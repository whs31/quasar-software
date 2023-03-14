#include "tcpdownloader.h"
#include "tcpdebug.h"
#include "disk/cachemanager.h"

#ifdef QMAKE_COMPILATOR
#include "QtGui/private/qzipreader_p.h"
#endif

#include <QDebug>
#include <QFile>
#include <QDir>
#include <QImage>

TCPDownloader::TCPDownloader(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(clientConnected()));
    if(!server->listen(QHostAddress(SConfig::get()->getComputerIP()), SConfig::get()->getLoaderPort().toUInt()))
    {
        qCritical() << "[TCP] TCP-IP server has failed to start.";
    } else {
        qInfo() << "[TCP] TCP-IP server started.";
    }
    timer = new QTimer();
    timer->setInterval(TCP_TIMEOUT);
    connect(timer, &QTimer::timeout, this, &TCPDownloader::connectionTimeout);
	//socket = new QTcpSocket(this);
}

void TCPDownloader::clientConnected(void)
{
    qInfo() << "[TCP] Trying to connect to SAR...";

	socket = server->nextPendingConnection();
	if(!socket)
	{
        qCritical() << "[TCP] NextPendingConnection returned nullptr. Aborting connection.";

		return;
	}
    connect(socket, &QTcpSocket::readyRead, this, &TCPDownloader::serverRead);
    connect(socket, &QTcpSocket::disconnected, this, &TCPDownloader::clientDisconnected);
    imageData64.clear();
    imageData.clear();
    readFile = &TCPDownloader::readFileInfo;
    success = false;
    timer->start();
    splitIndex = 0;

    qInfo() << "[TCP] SAR connected and ready to send image";
}

void TCPDownloader::clientDisconnected(void)
{
    socket->close();
    timer->stop();

    (fileSize == imageData.size()) ? qInfo() << "[TCP] Package fully received from SAR" : qWarning() << "[TCP] Something went wrong in receiving SAR image";

#ifdef QMAKE_COMPILATOR
    if(filename.contains(".zip"))
    {
        qDebug() << "[TCP] Received ZIP package for debugging!";

        QDir savefolder(CacheManager::getTcpDowloaderCache() + "/zip");
        if (!savefolder.exists())
            savefolder.mkpath(CacheManager::getTcpDowloaderCache() + "/zip");
        QFile save_archive(CacheManager::getTcpDowloaderCache() + "/zip/" + filename);
        if(save_archive.open(QIODevice::WriteOnly))
        {
            save_archive.write(imageData);
            save_archive.close();
        }
        QZipReader zip(CacheManager::getTcpDowloaderCache() + "/zip/" + filename);
        if (zip.exists()) {
            // вывод информации об архиве
            qDebug() << "Number of items in the zip archive =" << zip.count();
            foreach (QZipReader::FileInfo info, zip.fileInfoList())
            {
                if(info.isFile)
                    qDebug() << "File:" << info.filePath << info.size;
                else if (info.isDir)
                    qDebug() << "Dir:" << info.filePath;
                else
                    qDebug() << "SymLink:" << info.filePath;
            }
            QString filename_dir = filename;
            filename_dir.chop(4);
            QDir extractFolder(CacheManager::getTcpDowloaderCache() + "/zip/" + filename_dir);
            if (!extractFolder.exists())
                extractFolder.mkpath(CacheManager::getTcpDowloaderCache() + "/zip/" + filename_dir);
            zip.extractAll(CacheManager::getTcpDowloaderCache() + "/zip/" + filename_dir);

            QStringList initialFileList;
            extractFolder.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
            extractFolder.setNameFilters(QStringList("*.jpg"));
            for (QString entryString : extractFolder.entryList())
            {
                initialFileList.append(entryString.prepend(CacheManager::getTcpDowloaderCache() + "/zip/" + filename_dir + "/"));
            }
            if (!initialFileList.empty())
            {
                for(QString filestr : initialFileList)
                {
                    if(filestr.contains("e.jpg"))
                    {
                        QPixmap pixmap(filestr);
                        TCPDebug debug(nullptr, pixmap);
                        debug.exec();
                    }
                }
                TCPDebug debug(nullptr, initialFileList);
                debug.exec();
                if (savefolder.exists())
                    savefolder.removeRecursively();
            }
        }
    }
#endif

    if(not filename.contains(".zip"))
    {
        ImageManager::newImage(CacheManager::getTcpDowloaderCache() + "/" + filename, imageData);
    }
    emit receivingFinished();
}

void TCPDownloader::serverRead(void)
{
    (this->*readFile) (socket->readAll());
}

void TCPDownloader::readFileInfo(QByteArray data)
{
    readFile = &TCPDownloader::readFileBody;

    uint8_t i = data.indexOf('\n') + 1; // maybe + 1;
    filename = data.left(i - 1).data();
    memcpy(&fileSize, data.mid(i, sizeof(uint32_t)).data(), sizeof(uint32_t));

    i+=sizeof(uint32_t);

    qDebug() << "[TCP] Name:" << filename;
    qDebug() << "[TCP] Filesize:" << QString::number(fileSize / (1024)) << " kB";

    data.remove(0, i);

    timer->stop();
    timer->start();
    (this->*readFile)(data);
}

void TCPDownloader::readFileBody(QByteArray data)
{
    timer->stop();
    timer->start();
    if(data.size()){
        imageData.append(data);
    }
    progress();
}

float TCPDownloader::progress(){
    float f = (float)imageData.size() / fileSize;
    emit progressChanged(f * 100);
    return f;
}

void TCPDownloader::connectionTimeout(void){
    socket->close();
}
