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
    //pixMap = swapAlpha(pix);
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
    qDebug()<<i.hasAlphaChannel();
    return i;
}

QString ImageManager::getCacheDirectory(void)                   { return cacheDirectory;                                              }
QString ImageManager::getPNGDirectory(void)                     { return PNGDirectory;                                                }
