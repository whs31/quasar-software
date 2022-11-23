#include "imageprocessing.h"

ImageProcessing::ImageProcessing(LinkerQML* linker, MainWindow* parent) : mainWindow(parent), qmlLinker(linker)
{
    imageManager = new ImageManager;
}

bool ImageProcessing::getReadyStatus()
{
    if(!metadataList.empty()) { return 1; } return 0;
}

QStringList ImageProcessing::getEntryList(QString &path)
{
    QStringList strl = {};
    QDir initialDirectory(path);
    QStringList initialFileList;
    initialDirectory.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
    initialDirectory.setNameFilters(QStringList("*.jpg"));
    strl = initialDirectory.entryList();
    if(!strl.empty())
    {
            qDebug()<<"[FILEMANAGER] Metadata list contains "<<strl.length()<<" files";
        /*
         *          отрезаем формат, путь уже отрезан entryList(). Получается, str = имя файла без указания формата и пути к нему (mx_xx-xx-xxxx_xx-xx-xx)
         *          аналогичное действие должен провернуть метод ImageManager getDiff(), чтобы сравнивать конкретно имена файлов без расширений и путей.
         */
        for (int i = 0; i<strl.length(); i++) { strl[i].chop(4); }
        return strl;
    } else { qDebug()<<"[FILEMANAGER] Metadata list contains zero files, calling ImageManager..."; return {}; }
}

bool ImageProcessing::processPath(QString path)
{
    QElapsedTimer* profiler = new QElapsedTimer();
    profiler->start();
    diff.clear();
    diff = imageManager->getDiff(path, getEntryList(path));
        if(!diff.empty()) { qInfo()<<"[FILEMANAGER] Diff: "<<diff.length()<<" files"; }
        else { qInfo()<<"[FILEMANAGER] No difference between cache and path found. Image processing will be skipped"; }
    //diff received
    QStringList imageList = imageManager->CopyJPEG(path, diff);
        qCritical()<<"Time elapsed: ["<<profiler->elapsed()<<"] ms"; //1780 для 5 картинок
    if(!imageList.empty()) { notNull = true; } else { qDebug()<<"[IMG] Directory is empty, throwing warning window..."; notNull = false; }
    if(notNull)
    {
        qInfo()<<"[IMG] Imagelist fulfilled";
        profiler->restart();
        metadataList.clear();
        qmlLinker->clearImageArray();
        decode(imageList);
        updateLabels(0);
        mainWindow->updateImageManagerLabels(getVectorSize(), getFileCounter());
            qCritical()<<"Time elapsed: ["<<profiler->elapsed()<<"] ms"; //1032 для пяти картинок
    } else {
        QMessageBox warningDialogue;
        warningDialogue.setWindowTitle("Изображения не найдены!");
        warningDialogue.setIcon(QMessageBox::Warning);
        warningDialogue.setText("В выбранном каталоге не найдены изображения!");
        warningDialogue.exec();
    }
    if(getVectorSize()>1) { mainWindow->setPushButton_goRightEnabled(true); }
    return notNull;
}

void ImageProcessing::decode(QStringList filelist)
{
    image_metadata metaStruct = {0,0,0,0,0,0,0,0,0,"filename", "datetime", false};
    qDebug()<<"[IMG] Called decoding function for image from filelist of "<<filelist.length()<<" files";
    for (QString fileName : filelist)
    {
        QFile _qfile(fileName);
        if(_qfile.open(QIODevice::ReadOnly))
        {
            QByteArray rawData = _qfile.readAll();
            char *data = rawData.data();
            uint16_t *metaMarker = reinterpret_cast<uint16_t *>(data + JPEG_HEADER_SIZE);
            if(*metaMarker == 0xE1FF)
            {
                uint16_t *metaSize = reinterpret_cast<uint16_t *>(data + JPEG_HEADER_SIZE + 2);
                *metaSize = qToBigEndian(*metaSize) - 2;
                //const void* dataV;
                //memcpy(&dataV, (data+JPEG_HEADER_SIZE+4), *metaSize);
                memcpy(&metaStruct, (data+JPEG_HEADER_SIZE+4), *metaSize);
                metaStruct.filename = fileName;
                QFileInfo info(_qfile);
                QString pngPath = info.fileName();
                pngPath.chop(3); pngPath.append("png"); pngPath.prepend(imageManager->getPNGDirectory()+'/');
                QDir::toNativeSeparators(pngPath);
                metaStruct.filename = pngPath;
                QDateTime crDate = QFileInfo(_qfile).birthTime();
                metaStruct.datetime = crDate.toString("dd.MM в HH:mm:ss");

                //uint32_t newChecksum = getChecksum(dataV, (size_t)(*metaSize-JPEG_CHECKSUM_SIZE));

                //qDebug()<<newChecksum<<metaStruct.checksum;
                //qDebug()<<QString("%1").arg(newChecksum, 8, 16, QLatin1Char('0'));
                metaStruct.checksumMatch = 0; //(newChecksum==metaStruct.checksum) ? 1 : 0;
                        //qDebug()<<"[IMG] Decoded file ("<<filelist.indexOf(fileName)<<") successfully"; //засоряет дебаг
                metadataList.append(metaStruct);
                //make mask
                if(!diff.empty()&&imageManager->diffConvert(diff, 1).contains(info.fileName()))
                {
                    QImageReader reader(metaStruct.filename);
                    QSize sizeOfImage = reader.size();
                    int height = sizeOfImage.height();
                    int width = sizeOfImage.width();
                    qDebug()<<"[IMG] Making mask...";
                    imageManager->addAlphaMask(metaStruct.filename, width, height, 13, 30);
                } else {} //qDebug()<<"[IMG] Mask already applied, skipping..."; }
            }

        } else { qCritical()<<"[IMG] Decoding error!"; }
    }
}

void ImageProcessing::updateLabels(int structureIndex)
{
    QStringList tmp = metadataList[structureIndex].filename.split("/");
    QString cutFilename = tmp[tmp.size()-1];
    QString checksumHex = QString("%1").arg(metadataList[structureIndex].checksum, 8, 16, QLatin1Char('0'));
    mainWindow->updateImageMetaLabels(cutFilename,
                                      metadataList[structureIndex].latitude,
                                      metadataList[structureIndex].longitude,
                                      metadataList[structureIndex].dx,
                                      metadataList[structureIndex].dy,
                                      metadataList[structureIndex].x0,
                                      metadataList[structureIndex].y0,
                                      metadataList[structureIndex].angle,
                                      metadataList[structureIndex].driftAngle,
                                      checksumHex,
                                      metadataList[structureIndex].datetime,
                                      metadataList[structureIndex].checksumMatch);
}

uint32_t ImageProcessing::getChecksum(const void* data, size_t length, uint32_t previousCrc32)
{
    /*const uint32_t Polynomial = 0xEDB88320;
    uint32_t crc = ~previousCrc32;
    unsigned char* current = (unsigned char*) data;
    while (length--)
    {
        crc ^= *(uint32_t*)&current;
        current++;
        for (unsigned int j = 0; j < 8; j++)
            crc = (crc >> 1) ^ (-int(crc & 1) & Polynomial);
    }
    return ~crc;*/

    //этот метод будет переписан полностью на стороне РЛС
    return 0;
}

void ImageProcessing::showAllImages(bool showOnStart)
{
    for (image_metadata meta : metadataList)
    {
        if(meta.latitude!=0)
        {
            QImageReader reader(meta.filename);
            QSize sizeOfImage = reader.size();
            int height = sizeOfImage.height();
            //int width = sizeOfImage.width();
            qmlLinker->addImage(meta.latitude, meta.longitude, meta.dx, meta.dy, meta.x0, meta.y0, meta.angle, meta.filename, height);
            if(!showOnStart)
            {
                for(int i = 0; i<getVectorSize(); i++)
                {
                    qmlLinker->hideImage(i);
                }
            }
        }
    }
            qInfo()<<"[IMG] Images shown successfully";
}


int ImageProcessing::getFileCounter()           { return fileCounter;                                                           }
int ImageProcessing::getVectorSize()            { return metadataList.length();                                                 }
void ImageProcessing::goLeft()
{
    int totalFiles = getVectorSize()-1;
    if(fileCounter>0) { fileCounter--; updateLabels(fileCounter);                                       }
    if (fileCounter == 0) { mainWindow->setPushButton_goLeftEnabled(false);                             }
    if(fileCounter < totalFiles) { mainWindow->setPushButton_goRightEnabled(true);                      }
    if(notNull) { mainWindow->updateImageManagerLabels(getVectorSize(), getFileCounter());              }
}
void ImageProcessing::goRight()
{
    int totalFiles = getVectorSize()-1;
    if(fileCounter < totalFiles) { fileCounter++; updateLabels(fileCounter);                            }
    if(fileCounter > 0) { mainWindow->setPushButton_goLeftEnabled(true);                                }
    if (fileCounter == totalFiles) { mainWindow->setPushButton_goRightEnabled(false);                   }
    if(notNull) { mainWindow->updateImageManagerLabels(getVectorSize(), getFileCounter());              }
}
