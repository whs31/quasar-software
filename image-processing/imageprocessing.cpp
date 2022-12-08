#include "imageprocessing.h"

ImageProcessing::ImageProcessing(LinkerQML* linker) : qmlLinker(linker)
{
    imageManager = new ImageManager;
}

bool ImageProcessing::getReadyStatus()
{
    if(!metadataList.empty()) return 1;
    return 0;
}

void ImageProcessing::clearCache()
{
    metadataList.clear();
    qmlLinker->clearImageArray();
    ImageManager::clearCache(ClearMode::ClearAll);
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
        Debug::Log("[FILEMANAGER] Metadata list contains "+QString::number(strl.length())+" files");
        /*
         *          отрезаем формат, путь уже отрезан entryList(). Получается, strl[i] = имя файла без указания формата и пути к нему (mx_xx-xx-xxxx_xx-xx-xx)
         *          аналогичное действие должен провернуть метод ImageManager getDiff(), чтобы сравнивать конкретно имена файлов без расширений и путей.
         */
        for (int i = 0; i<strl.length(); i++) { strl[i].chop(4); }
        return strl;
    } else {
        Debug::Log("[FILEMANAGER] Metadata list contains zero files, calling ImageManager...");
        return {};
    }
}

void ImageProcessing::imageChecklistLoop()
{
    if(getReadyStatus()==true)
    {
        for(int i = 0; i<getVectorSize(); i++)
        {
            if(imageChecklist[i]==true)
            {
                qmlLinker->showImage(i);
            } else {
                qmlLinker->hideImage(i);
            }
        }
    }
}

bool ImageProcessing::InitialScan() //recall after changing settings
{
    Profiler* profiler = new Profiler("Профайлер полного сканирования"); 
    profiler->Start();
    QString initialPath = (SConfig::USELOADER) ? SConfig::CACHEPATH : SConfig::PATH;
    diff.clear();
    diff = imageManager->GetDiff(getEntryList(initialPath));
    profiler->Stop("Diff");
    profiler->Start();
    QStringList imageList = imageManager->GetInitialList(initialPath, diff);
    profiler->Stop("PNG saving");
    if(!diff.empty())
    {
        Debug::Log("[FILEMANAGER] Diff: "+QString::number(diff.length())+" files");
    } else {
        Debug::Log("?[FILEMANAGER] No difference between cache and path found. Image processing will be skipped");
    }
    
    if(!imageList.empty())
    {
        notNull = true;
        qInfo()<<"[IMG] Imagelist fulfilled";

        metadataList.clear();
        profiler->Start();
        qmlLinker->clearImageArray();
        profiler->Stop("QML array clear");
        profiler->Start();
        Decode(imageList, DecodeMode::Initial);
        profiler->Stop("Decode and alpha mask apply");
        UpdateLabels(0);
        profiler->ShowProfile();
        emit updateTopLabels(getVectorSize(), getFileCounter());
    } else {
        notNull = false;
        Debug::Log("![IMG] Directory is empty, throwing warning window...");
        QMessageBox warningDialogue;
        warningDialogue.setWindowTitle("Изображения не найдены!");
        warningDialogue.setIcon(QMessageBox::Warning);
        warningDialogue.setText("В выбранном каталоге не найдены изображения!");
        warningDialogue.exec();
    }
    if(getVectorSize()>1)
    {
        emit(setRightButton(true));
    }
    if(getReadyStatus())
    {
        for(int i = 0; i<getVectorSize(); i++)
        {
            imageChecklist.append(SConfig::SHOWIMAGEONSTART);
        }
        showInitialScanResult(SConfig::SHOWIMAGEONSTART);
    }
    emit enableImageBar(notNull);
    return notNull;
}

bool ImageProcessing::PartialScan()
{
    Profiler* profiler = new Profiler("Профайлер частичного сканирования"); 
    profiler->Start();
    QString initialPath = (SConfig::USELOADER) ? SConfig::CACHEPATH : SConfig::PATH;
    bool foundNew = false;
    diff.clear();
    diff = imageManager->GetDiff(getEntryList(initialPath));
    profiler->Stop("Diff");

    profiler->Start();
    QStringList imageList = imageManager->GetPartialList(initialPath, diff);
    if(!diff.empty())
    {
        Debug::Log("[FILEMANAGER] Diff: "+QString::number(diff.length())+" files");
    } else {
        Debug::Log("[FILEMANAGER] Partial scan found no difference to process");
    }
    profiler->Stop("PNG saving");
    profiler->Start();
    if(!imageList.empty())
    {
        Debug::Log("?[IMG] Imagelist fulfilled");
        foundNew = true;
        notNull = true;
        if(getVectorSize()>1)
        {
            emit(setRightButton(true));
        }
        emit enableImageBar(true);
        Decode(imageList, DecodeMode::Partial);

        emit updateTopLabels(getVectorSize(), getFileCounter());
    } else {
        Debug::Log("[IMG] Partial scan found no images to process");
        foundNew = false;
    }
    profiler->Stop("Decoding and alpha mask apply");
    if(foundNew)
    {
        emit(setRightButton(true));
    }
    profiler->Start();
    if(getReadyStatus())
    {
        for(int i = getVectorSize()-newImagesCounter; i<getVectorSize(); i++)
        {
            imageChecklist.append(SConfig::SHOWIMAGEONSTART);
        }
        showPartialScanResult();
    }
    profiler->Stop("UI and QML display");
    profiler->ShowProfile();
    return foundNew;
}

void ImageProcessing::Decode(QStringList filelist, DecodeMode mode)
{
    image_metadata metaStruct = {0,0,0,0,0,0,0,0,0,0,0,0,"-", "-", false, "-"};
    Debug::Log("?[IMG] Called decoding function for image from filelist of "+QString::number(filelist.length())+" files");
    for (int s = 0; s<filelist.length(); s++)
    {
        QString fileName = filelist[s];
        QFile _qfile(fileName);
        if(_qfile.open(QIODevice::ReadOnly))
        {
            QByteArray rawData = _qfile.readAll();
            char *data = rawData.data();
            uint16_t *metaMarker = reinterpret_cast<uint16_t *>(data + JPEG_HEADER_SIZE);
            if(*metaMarker == 0xE1FF)
            {
                //заполнение структуры метаданными
                uint16_t *metaSize = reinterpret_cast<uint16_t *>(data + JPEG_HEADER_SIZE + 2);
                *metaSize = qToBigEndian(*metaSize) - 2;
                memcpy(&metaStruct, (data+JPEG_HEADER_SIZE+4), *metaSize);
                metaStruct.filename = fileName;

                //добавление в структуру имени файла (.png)
                QFileInfo info(_qfile);
                QString pngPath = info.fileName();
                pngPath.chop(3);
                pngPath.append("png");
                pngPath.prepend(ImageManager::getPNGDirectory()+'/');
                QDir::toNativeSeparators(pngPath);
                metaStruct.filename = pngPath;

                //добавление в структуру даты создания файла
                QDateTime crDate = QFileInfo(_qfile).birthTime();
                metaStruct.datetime = crDate.toString("dd.MM в HH:mm:ss");

                //проверка контрольной суммы
                void* structData = (void *) malloc(1024);
                memcpy((char*)structData, (void*)&metaStruct, *metaSize);
                uint32_t recalculatedChecksum = SChecksum::calculateChecksum(structData, *metaSize);
                QString recalculatedChecksumHex = QString("%1").arg(recalculatedChecksum, 8, 16, QLatin1Char('0'));
                qCritical()<<recalculatedChecksumHex;

                metaStruct.checksumMatch = (recalculatedChecksum == metaStruct.checksum) ? 1 : 0;

                //геометрические преобразования
                if(SConfig::METAANGLEINRADIANS)
                {
                    metaStruct.angle = SMath::radiansToDegrees(metaStruct.angle) + SConfig::METAANGLECORRECTION;
                    metaStruct.driftAngle = SMath::radiansToDegrees(metaStruct.driftAngle);
                    metaStruct.div = SMath::radiansToDegrees(metaStruct.div);
                }

                //создание маски альфа-канала
                QImageReader reader(metaStruct.filename);
                QSize sizeOfImage = reader.size();
                int height = sizeOfImage.height();
                int width = sizeOfImage.width();
                if(SConfig::USEBASE64)
                {
                    Debug::Log("[IMG] Using base64 encoding, making mask...");
                    metaStruct.base64encoding = imageManager->addAlphaMask(metaStruct.filename, width, height, (metaStruct.div == 0) ? SConfig::AZIMUTH : metaStruct.div, 30, 0, 0, MaskFormat::Geometric);
                    if(metaStruct.base64encoding.length()<100)
                    {
                        Debug::Log("!![IMG] Something went wrong (base64) "+metaStruct.base64encoding);
                    }
                }
                else if(!diff.empty()&&ImageManager::diffConvert(diff, ImageFormat::JPEG).contains(info.fileName()))
                {
                    Debug::Log("[IMG] Using saving to disk, making mask...");
                    imageManager->addAlphaMask(metaStruct.filename, width, height, 13, 30, 0, 0, MaskFormat::Geometric);
                }
                metadataList.append(metaStruct);
                if(mode == DecodeMode::Partial)
                {
                    newImagesCounter++;
                }
            } else {
                Debug::Log("!![IMG] Marker error!");
            }
        } else {
            Debug::Log("!![IMG] Decoding error!");
        }
    }
}

void ImageProcessing::UpdateLabels(int structureIndex)
{
    QStringList tmp = metadataList[structureIndex].filename.split("/");
    QString cutFilename = tmp[tmp.size()-1];
    QString checksumHex = QString("%1").arg(metadataList[structureIndex].checksum, 8, 16, QLatin1Char('0'));
    emit updateMetaLabels(cutFilename,
                          metadataList[structureIndex].latitude,
                          metadataList[structureIndex].longitude,
                          metadataList[structureIndex].dx,
                          metadataList[structureIndex].dy,
                          metadataList[structureIndex].x0,
                          metadataList[structureIndex].y0,
                          metadataList[structureIndex].angle,
                          metadataList[structureIndex].driftAngle,
                          metadataList[structureIndex].lx,
                          metadataList[structureIndex].ly,
                          metadataList[structureIndex].div,
                          checksumHex,
                          metadataList[structureIndex].datetime,
                          metadataList[structureIndex].checksumMatch);
}

void ImageProcessing::showInitialScanResult(bool showOnStart)
{
    if(!metadataList.isEmpty())
    {

        for (image_metadata meta : metadataList)
        {
            if(meta.latitude!=0)
            {
                QImageReader reader(meta.filename);
                QSize sizeOfImage = reader.size();

                qmlLinker->addImage(meta.latitude, meta.longitude, meta.dx, meta.dy, meta.x0, meta.y0, meta.angle, meta.filename, sizeOfImage.height(), meta.base64encoding);

                if(meta.base64encoding.length()<100 && SConfig::USEBASE64)
                {
                    Debug::Log("!![QML] Something went wrong");
                }

                if(!showOnStart)
                {
                    for(int i = 0; i<getVectorSize(); i++)
                    {
                        qmlLinker->hideImage(i);
                    }
                }
            }
        }
    } else {
        Debug::Log("![IMG] Empty image list!");
    }
}

void ImageProcessing::showPartialScanResult()
{
    if(newImagesCounter != 0)
    {
        for(int i = 1; i <= newImagesCounter; i++)
        {
            if(metadataList[metadataList.length()-i].latitude!=0)
            {
                QImageReader reader(metadataList[metadataList.length()-i].filename);
                QSize sizeOfImage = reader.size();
                qmlLinker->addImage(metadataList[metadataList.length()-i].latitude, metadataList[metadataList.length()-i].longitude,
                        metadataList[metadataList.length()-i].dx, metadataList[metadataList.length()-i].dy,
                        metadataList[metadataList.length()-i].x0, metadataList[metadataList.length()-i].y0,
                        metadataList[metadataList.length()-i].angle,
                        metadataList[metadataList.length()-i].filename,
                        sizeOfImage.height(), metadataList[metadataList.length()-i].base64encoding);

                if(metadataList[metadataList.length()-i].base64encoding.length()<100 && SConfig::USEBASE64)
                {
                    Debug::Log("!![QML] Something went wrong");
                }
            }
        }
        Debug::Log("?[IMG] Some new images shown successfully");
        newImagesCounter = 0;
    } else {
        Debug::Log("?[IMG] No new images, skipping qml part");
    }

}


int ImageProcessing::getFileCounter()
{
    return fileCounter;
}

int ImageProcessing::getVectorSize()
{
    return metadataList.length();
}

void ImageProcessing::goLeft()
{
    int totalFiles = getVectorSize()-1;
    if(fileCounter>0)
    {
        fileCounter--;
        UpdateLabels(fileCounter);
    }
    if (fileCounter == 0)
    {
        emit(setLeftButton(false));
    }
    if(fileCounter < totalFiles)
    {
        emit(setRightButton(true));
    }
    if(notNull)
    {
        emit updateTopLabels(getVectorSize(), getFileCounter());
    }
}
void ImageProcessing::goRight()
{
    int totalFiles = getVectorSize()-1;
    if(fileCounter < totalFiles)
    {
        fileCounter++; UpdateLabels(fileCounter);
    }
    if(fileCounter > 0)
    {
        emit(setLeftButton(true));
    }
    if (fileCounter == totalFiles)
    {
        emit(setRightButton(false));
    }
    if(notNull)
    {
        emit updateTopLabels(getVectorSize(), getFileCounter());
    }
}
