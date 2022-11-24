#include "imagemanager.h"

ImageManager::ImageManager(QObject *parent) : QObject(parent)
{
    cacheDirectory = QCoreApplication::applicationDirPath()+"/cache/"+"pjpgc";
    QDir dir(cacheDirectory);
    if (!dir.exists()){ dir.mkpath(cacheDirectory); }
    PNGDirectory = QCoreApplication::applicationDirPath()+"/cache/"+"pngc";
    QDir pngdir(PNGDirectory);
    if(!pngdir.exists()) { pngdir.mkpath(PNGDirectory); }
    TCPDirectory = QCoreApplication::applicationDirPath()+"/cache/"+"tcpipdc";
    QDir tcpdir(TCPDirectory);
    if(!tcpdir.exists()) { tcpdir.mkpath(TCPDirectory); }
    SConfig::CACHEPATH = TCPDirectory;

            qInfo()<<"[FILEMANAGER] Working directory: "<<cacheDirectory;
            qInfo()<<"[FILEMANAGER] .png directory: "<<PNGDirectory;
            qInfo()<<"[FILEMANAGER] TCP Downloader directory: "<<TCPDirectory;
    //на случай если ne захочется кешировать в отдельную папку
    //PNGDirectory = cacheDirectory;
}

QStringList ImageManager::getDiff(const QString &path, QStringList existingFileList)
{
    QDir pngDirectory(getPNGDirectory());
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



QString ImageManager::MakePNG(QString jpeg)
{
            qDebug()<<"[FILEMANAGER] Making png file out of "<<jpeg;
    QFile file(jpeg);
    QFileInfo f(file);
    QString filename = f.fileName();
    filename.chop(3); filename.append("png");
    QImage pixMap(jpeg);
    pixMap = enableAlphaSupport(pixMap);
    QString finalFile = PNGDirectory+'/'+filename;
    QDir::toNativeSeparators(finalFile);
    pixMap.save(finalFile);
    return finalFile;
}

QImage ImageManager::swapAlpha(QImage i)
{
    QImage alphaImage = i;
    alphaImage.createMaskFromColor(QColor("black").rgb(), Qt::MaskOutColor);
    i.setAlphaChannel(alphaImage);
    return i;
}

QImage ImageManager::enableAlphaSupport(QImage i)                                     //      этот метод нужен для конверсии изображения
{                                                                                     //      в формат, поддерживающий прозрачность
    QImage sample(i.width(),i.height(), QImage::Format_ARGB32_Premultiplied);
    sample.fill(QColor(254,254,254));
    i.setAlphaChannel(sample);
    return i;
}

bool ImageManager::saveRawData(QByteArray data, QString filename)
{
    QPixmap image;
    image.loadFromData(data);
    QString path = getTCPDirectory();
    path.append("/");
    path.append(filename);
    QDir::toNativeSeparators(path);
    image.save(path);
}

bool ImageManager::addAlphaMask(QString path, float width, float height, float thetaAzimuth, float rayInitialWidth, float horizontalCut, float driftAngle)
{
    QImage base(path);
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
    base.save(path);
}

QString ImageManager::getCacheDirectory(void)                   { return cacheDirectory;                                              }
QString ImageManager::getPNGDirectory(void)                     { return PNGDirectory;                                                }
QString ImageManager::getTCPDirectory(void)                     { return TCPDirectory;                                                }
