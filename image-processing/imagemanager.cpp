#include "imagemanager.h"

QString ImageManager::cacheDirectory;
QString ImageManager::PNGDirectory;
QString ImageManager::TCPDirectory;
ImageManager::ImageManager(QObject *parent) : QObject(parent)
{
    ImageManager::setupCache();
            qInfo()<<"[FILEMANAGER] Working directory: "<<ImageManager::cacheDirectory;
            qInfo()<<"[FILEMANAGER] .png directory: "<<ImageManager::PNGDirectory;
            qInfo()<<"[FILEMANAGER] TCP Downloader directory: "<<ImageManager::TCPDirectory;
    //на случай если ne захочется кешировать в отдельную папку
    //PNGDirectory = cacheDirectory;
}

QStringList ImageManager::getDiff(const QString &path, QStringList existingFileList)
{
    QDir pngDirectory(ImageManager::getPNGDirectory());
    QStringList pngFileList;
    QStringList diff;
    pngDirectory.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
    pngDirectory.setNameFilters(QStringList("*.png"));
    for (QString entryString : pngDirectory.entryList()) { pngFileList.append(entryString); }
    for (int i = 0; i<pngFileList.length(); i++) { pngFileList[i].chop(4); }
        qDebug()<<"[FILEMANAGER] Found "<<pngFileList.length()<<" files in cache";
    for(QString str : existingFileList) { if(!pngFileList.contains(str)) { diff.append(str); } }
    return diff;
}

QStringList ImageManager::CopyJPEG(const QString &path, QStringList diff)
{
    QDir initialDirectory(path);
    QStringList initialFileList;
    QStringList jpgFileList;
    initialDirectory.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
    initialDirectory.setNameFilters(QStringList("*.jpg"));
    for (QString entryString : initialDirectory.entryList())
    {
        initialFileList.append(entryString.prepend(path+"/"));
    }
    if(!initialFileList.empty())
    {
        for ( QString initialFile : initialFileList ) {
            QFileInfo fileInfo(initialFile);
            QString jpegFile = cacheDirectory + '/' + fileInfo.fileName();
            QDir::toNativeSeparators(jpegFile);
            //diff convert
            //qWarning()<<diffConvert(diff, 1);
            if(!diff.empty()&&diffConvert(diff, ImageFormat::JPEG).contains(fileInfo.fileName()))
            {
                bool result = QFile::copy(initialFile, jpegFile);
                result==true ? qDebug()<<"[FILEMANAGER] Copy success " : qWarning()<<"[FILEMANAGER] File already existing at working .png cache (probably diff error)!";
                MakePNG(jpegFile);
            }
            jpgFileList.append(jpegFile);
        }
        return jpgFileList;
    } return {}; //.empty() = true
}

bool ImageManager::saveRawData(QByteArray data, QString filename)
{
    data.reserve(sizeof(data));

    QString path = ImageManager::getTCPDirectory();
    path.append("/");
    path.append(filename);
    QDir::toNativeSeparators(path);
    QSaveFile file(path);
    file.open(QIODevice::WriteOnly);
    file.write(data);
    file.commit();
    return true;
}

QString ImageManager::addAlphaMask(QString path, float width, float height, float thetaAzimuth, float rayInitialWidth, float horizontalCut, float driftAngle, MaskFormat format)
{
    QImage base(path);
    if(format == 0 || format == 2)
    {

        QPainter painter;
        painter.begin(&base);
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        //painter.fillRect(base.rect(), QColor(0, 0, 0, 120));
        painter.setPen(QPen(Qt::transparent, 2));
        painter.setRenderHint(QPainter::Antialiasing);
        const int top[8] = {
            0, (int)(height/2+rayInitialWidth),
            0, (int)height,
            (int)width, (int)height,
            (int)width, static_cast<int>((height/2)+width*(qTan(qDegreesToRadians(thetaAzimuth/2))))
        };
        const int bottom[8] = {
            0, (int)(height/2-rayInitialWidth),
            0, 0,
            (int)width, 0,
            (int)width, static_cast<int>((height/2)-width*(qTan(qDegreesToRadians(thetaAzimuth/2))))
        };
        QPolygon p1, p2;
        p1.setPoints(4, top); p2.setPoints(4, bottom);
        painter.drawPolygon(p1);
        painter.drawPolygon(p2);
        QPainterPath fillp;
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::transparent);
        fillp.addPolygon(p1); fillp.addPolygon(p2);
        painter.fillPath(fillp, brush);
        painter.end();
    }
    if(format == 1 || format == 2)
    {
        QImage alphaImage = base;
        alphaImage.createMaskFromColor(QColor("black").rgb(), Qt::MaskOutColor);
        base.setAlphaChannel(alphaImage);
    }
    if(SConfig::USEBASE64)
    {
        QString r = convertToBase64(base);
        return r;
    } else {
        bool s = base.save(path); //rework
    }
    return "";
}

QString ImageManager::getCacheDirectory(void)
{
    return ImageManager::cacheDirectory;
}
QString ImageManager::getPNGDirectory(void)
{
    return ImageManager::PNGDirectory;
}
QString ImageManager::getTCPDirectory(void)
{
    return ImageManager::TCPDirectory;
}

void ImageManager::clearCache(ClearMode mode)
{
    if(mode == 0||mode == 1)
    {
        QDir tcpdir(ImageManager::TCPDirectory);
        if(tcpdir.exists()) { tcpdir.removeRecursively(); }
    }
    if(mode == 0||mode == 2)
    {
        QDir dir(ImageManager::cacheDirectory);
        if (dir.exists()) { dir.removeRecursively(); }
        QDir pngdir(ImageManager::PNGDirectory);
        if(pngdir.exists()) { pngdir.removeRecursively(); }
    }
    qWarning()<<"[FILEMANAGER] Cache cleared ("<<mode<<")";
    ImageManager::setupCache();
}

void ImageManager::setupCache(void)
{
    ImageManager::cacheDirectory = QCoreApplication::applicationDirPath()+"/cache/"+"pjpgc";
    QDir dir(ImageManager::cacheDirectory);
    if (!dir.exists()){ dir.mkpath(cacheDirectory); }
    ImageManager::PNGDirectory = QCoreApplication::applicationDirPath()+"/cache/"+"pngc";
    QDir pngdir(ImageManager::PNGDirectory);
    if(!pngdir.exists()) { pngdir.mkpath(ImageManager::PNGDirectory); }
    ImageManager::TCPDirectory = QCoreApplication::applicationDirPath()+"/cache/"+"tcpipdc";
    QDir tcpdir(ImageManager::TCPDirectory);
    if(!tcpdir.exists()) { tcpdir.mkpath(ImageManager::TCPDirectory); }
    SConfig::CACHEPATH = ImageManager::TCPDirectory;
    qDebug()<<"[FILEMANAGER] Cache created";
}

/*
 *            format:
 * { 0 1 2 } => { blank .jpg .png }
 */
QStringList ImageManager::diffConvert(QStringList diff, ImageFormat format)
{
    switch (format) {
    case 0:
        for(int i = 0; i<diff.length(); i++)
        {
            diff[i].chop(4);
        }
        break;
    case 1:
        for(int i = 0; i<diff.length(); i++)
        {
            diff[i].append(".jpg");
        }
        break;
    case 2:
        for(int i = 0; i<diff.length(); i++)
        {
            diff[i].append(".png");
        }
        break;
    default:
        break;
    } return diff;
}

QImage ImageManager::enableAlphaSupport(QImage i)                                     //      этот метод нужен для конверсии изображения
{                                                                                     //      в формат, поддерживающий прозрачность
    QImage sample(i.width(),i.height(), QImage::Format_ARGB32_Premultiplied);
    sample.fill(QColor(254,254,254));
    i.setAlphaChannel(sample);
    return i;
}

QString ImageManager::convertToBase64(QImage image)
{
    QByteArray arr;
    QBuffer buffer(&arr);
    image.save(&buffer, "PNG");
    QString encoded = QString::fromLatin1(arr.toBase64().data());
    return encoded;
}

QString ImageManager::MakePNG(QString jpeg)
{
            qDebug()<<"[FILEMANAGER] Making png file out of "<<jpeg;
    QFile file(jpeg);
    QFileInfo f(file);
    QString filename = f.fileName();
    filename.chop(3); filename.append("png");
    QImage pixMap(jpeg);
    pixMap = enableAlphaSupport(pixMap);
    QString finalFile = ImageManager::PNGDirectory+'/'+filename;
    QDir::toNativeSeparators(finalFile);
    pixMap.save(finalFile);
    return finalFile;
}







