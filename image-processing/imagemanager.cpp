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

bool ImageManager::CopyJPEG(const QString &path)
{
    QDir directory(path);
    QStringList fileList;
    directory.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
    directory.setNameFilters(QStringList("*.jpg"));
    QStringList entry_list = directory.entryList();
    for (QString entryString : entry_list)
    {
        fileList.append(entryString.prepend(path+"/"));
    }
    if(!fileList.empty())
    {
        for ( QString f : fileList ) {
            QFileInfo fileInfo(f);
            QString destinationFile = cacheDirectory + QDir::separator() + fileInfo.fileName();
            bool result = QFile::copy(f, destinationFile);
            result==true ? qDebug()<<"[FILEMANAGER] Copy success" : qWarning()<<"[FILEMANAGER] File already existing at working .png cache, skipping...";
            MakePNG(destinationFile);
        }
        return true;
    } return false;
}

bool ImageManager::MakePNG(QString jpeg)
{
    qDebug()<<"[FILEMANAGER] Making png file out of "<<jpeg;
    QFile file(jpeg);
    QFileInfo f(file);
    QString filename = f.fileName();
    filename.chop(3); filename.append("png");
    QImage pix(jpeg);
    swapAlpha(pix);
    bool b = pix.save(PNGDirectory+QDir::separator()+filename);
    return b;
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
