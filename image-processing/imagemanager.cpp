#include "imagemanager.h"

ImageManager::ImageManager(QObject *parent) : QObject(parent)
{
    cacheDirectory = QCoreApplication::applicationDirPath()+QDir::separator()+"image-cache";
    QDir dir(cacheDirectory);
    if (!dir.exists()){
      dir.mkdir(cacheDirectory);
    }
    PNGDirectory = QCoreApplication::applicationDirPath()+QDir::separator()+"png-cache";
    QDir pngdir(PNGDirectory);
    if(!pngdir.exists())
    {
        pngdir.mkdir(PNGDirectory);
    }
    qInfo()<<"[FILEMANAGER] Working directory: "<<cacheDirectory<<", .png directory: "<<PNGDirectory;
    //на случай если ne захочется кешировать в отдельную папку
    //PNGDirectory = cacheDirectory;
}

QStringList ImageManager::CopyJPEG(const QString &path)
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
            bool result = QFile::copy(initialFile, jpegFile);
            jpgFileList.append(jpegFile);
            result==true ? qDebug()<<"[FILEMANAGER] Copy success" : qWarning()<<"[FILEMANAGER] File already existing at working .png cache, skipping...";
            MakePNG(jpegFile);
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
    pixMap.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    pixMap = evilFormatConversion(pixMap);
    QString finalFile = PNGDirectory+'/'+filename;
    QDir::toNativeSeparators(finalFile);
    pixMap.save(finalFile);
    qDebug()<<pixMap.hasAlphaChannel();
    return finalFile;
}

QImage ImageManager::swapAlpha(QImage i)
{
    QImage alphaImage = i;
    alphaImage.createMaskFromColor(QColor("black").rgb(), Qt::MaskOutColor);
    i.setAlphaChannel(alphaImage);
    qDebug()<<i.hasAlphaChannel();
    return i;
}

QImage ImageManager::evilFormatConversion(QImage i)                                     //      этот метод нужен для конверсии изображения
{                                                                                       //      в формат, поддерживающий прозрачность
    QImage sample(i.width(),i.height(), QImage::Format_ARGB32_Premultiplied);
    sample.fill(QColor(254,254,254));
    i.setAlphaChannel(sample);
    return i;
}

bool ImageManager::addAlphaMask(QString path, float width, float height, float thetaAzimuth, float rayInitialWidth, float horizontalCut, float driftAngle)
{
    QImage base(path);
    base.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    qDebug()<<base.hasAlphaChannel();
    QPainter painter;
    painter.begin(&base);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    //painter.fillRect(base.rect(), QColor(0, 0, 0, 120));
    painter.setPen(QPen(Qt::transparent, 2));
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
    qDebug()<<base.hasAlphaChannel();
}

QString ImageManager::getCacheDirectory(void)                   { return cacheDirectory;                                              }
QString ImageManager::getPNGDirectory(void)                     { return PNGDirectory;                                                }
