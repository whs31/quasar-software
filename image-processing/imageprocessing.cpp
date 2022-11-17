#include "imageprocessing.h"

ImageProcessing::ImageProcessing(QObject *parent) : QObject (parent)
{
    mainWindow = MainWindow::getMainWinPtr();
    imageManager = new ImageManager;
}

bool ImageProcessing::getReadyStatus()
{
    if(!imageList.empty()) { return 1; } return 0;
}

void ImageProcessing::decode(QStringList filelist)
{
    image_metadata metaStruct = {0,0,0,0,0,0,0,0,0,"filename", "datetime", false};
    qDebug()<<"[IMG] Called decoding function for image from filelist of "<<filelist.length()<<" files";
    for (QString fileName : filelist)
    {
        //qWarning()<<filelist;
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
                const void* dataV;
                //memcpy(&dataV, (data+JPEG_HEADER_SIZE+4), *metaSize);
                memcpy(&metaStruct, (data+JPEG_HEADER_SIZE+4), *metaSize);
                metaStruct.filename = fileName;
                QDateTime crDate = QFileInfo(_qfile).birthTime();
                metaStruct.datetime = crDate.toString("dd.MM в HH:mm:ss");

                //uint32_t newChecksum = getChecksum(dataV, (size_t)(*metaSize-JPEG_CHECKSUM_SIZE));

                //qDebug()<<newChecksum<<metaStruct.checksum;
                //qDebug()<<QString("%1").arg(newChecksum, 8, 16, QLatin1Char('0'));
                metaStruct.checksumMatch = 1;//(newChecksum==metaStruct.checksum) ? 1 : 0;
                qDebug()<<"[IMG] Decoded file ("<<filelist.indexOf(fileName)<<") successfully";
                metadataList.append(metaStruct);
            }

        } else { qDebug()<<"[IMG] Decoding error!"; }
    }
}

bool ImageProcessing::processPath(QString path)
{
    notNull = imageManager->CopyJPEG(path);

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
        notNull = true;
        qInfo()<<"[IMG] Imagelist fulfilled";
        imageList.clear();
        metadataList.clear();
        for ( QString f : fileList ) {
            imageList.append(f);
        }
        QQuickItem*  qml = mainWindow->ui->map->rootObject();
        QMetaObject::invokeMethod(qml, "clearImageArray");
        decode(imageList);
        updateLabels(0);
    } else {
        notNull = false;
        QMessageBox warningDialogue;
        warningDialogue.setWindowTitle("Изображения не найдены!");
        warningDialogue.setIcon(QMessageBox::Warning);
        warningDialogue.setText("В выбранном каталоге не найдены изображения!");
        warningDialogue.exec();
    }
    mainWindow->ui->pushButton_goRight->setEnabled(true);
    return notNull;
}

void ImageProcessing::updateLabels(int structureIndex)
{
    QStringList tmp = metadataList[structureIndex].filename.split("/");
    QString cutFilename = tmp[tmp.size()-1];
        mainWindow->ui->label_c_metaFilename->setText(cutFilename);
        mainWindow->ui->label_c_metaLat->setText(QString::number(metadataList[structureIndex].latitude));
        mainWindow->ui->label_c_metaLon->setText(QString::number(metadataList[structureIndex].longitude));
        mainWindow->ui->label_c_metaDx->setText(QString::number(metadataList[structureIndex].dx));
        mainWindow->ui->label_c_metaDy->setText(QString::number(metadataList[structureIndex].dy));
        mainWindow->ui->label_c_metaX0->setText(QString::number(metadataList[structureIndex].x0));
        mainWindow->ui->label_c_metaY0->setText(QString::number(metadataList[structureIndex].y0));
        mainWindow->ui->label_c_metaAngle->setText(QString::number(metadataList[structureIndex].angle));
        mainWindow->ui->label_c_metaDAngle->setText(QString::number(metadataList[structureIndex].driftAngle));
        QString checksumHex = QString("%1").arg(metadataList[structureIndex].checksum, 8, 16, QLatin1Char('0'));
        mainWindow->ui->label_c_metaChecksum->setText(checksumHex);
        mainWindow->ui->label_c_metaTime->setText(metadataList[structureIndex].datetime);
        if(metadataList[structureIndex].checksumMatch) { mainWindow->ui->label_c_checksumSuccess->setText(mainWindow->HtmlColorSuccess+"да"+mainWindow->HtmlColorEnd); }
        else { mainWindow->ui->label_c_checksumSuccess->setText(mainWindow->HtmlColorFailure+"нет"+mainWindow->HtmlColorEnd); }
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

void ImageProcessing::showAllImages()
{
    bool tmp_showOnStart = false; //replace by config value <--------------------------------------------------------
    for (image_metadata meta : metadataList)
    {
        if(meta.latitude!=0)
        {
            QQuickItem*  qml = mainWindow->ui->map->rootObject();
            QImageReader reader(meta.filename);
            QSize sizeOfImage = reader.size();
            int height = sizeOfImage.height();
            //int width = sizeOfImage.width();
            QMetaObject::invokeMethod(qml, "addImage",
                        Q_ARG(QVariant, (float)meta.latitude),
                        Q_ARG(QVariant, (float)meta.longitude),
                        Q_ARG(QVariant, meta.dx),
                        Q_ARG(QVariant, meta.dy),
                        Q_ARG(QVariant, meta.x0),
                        Q_ARG(QVariant, meta.y0),
                        Q_ARG(QVariant, meta.angle),
                        Q_ARG(QVariant, meta.filename),
                        Q_ARG(QVariant, height)
                    );
            if(!tmp_showOnStart) // <--------------------------------------------------------
            {
                for(int i = 0; i<getVectorSize(); i++)
                {
                    QMetaObject::invokeMethod(qml, "hideImage",
                                                  Q_ARG(QVariant, i));
                }
            }
        }
    }
    qInfo()<<"[IMG] Images shown successfully";
}


int ImageProcessing::getFileCounter()
{
    return fileCounter;
}

int ImageProcessing::getVectorSize()
{
    return imageList.length();
}

void ImageProcessing::goLeft()
{
    int totalFiles = getVectorSize()-1;

    if(fileCounter>0)
    {
        fileCounter--;
        updateLabels(fileCounter);
    }
    if (fileCounter == 0) {
        mainWindow->ui->pushButton_goLeft->setEnabled(false);
    }
    if(fileCounter < totalFiles)
    {
        mainWindow->ui->pushButton_goRight->setEnabled(true);
    }
    updateUpperLabels();
}

void ImageProcessing::goRight()
{
    int totalFiles = getVectorSize()-1;
    if(fileCounter < totalFiles)
    {
        fileCounter++;
        updateLabels(fileCounter);
    }
    if(fileCounter > 0)
    {
        mainWindow->ui->pushButton_goLeft->setEnabled(true);
    }
    if (fileCounter == totalFiles) {
        mainWindow->ui->pushButton_goRight->setEnabled(false);
    }
    updateUpperLabels();
}

void ImageProcessing::updateUpperLabels()
{
    if(notNull) {  }
    mainWindow->ui->label_c_foundImages->setText(
                "Найдено "
                +mainWindow->HtmlBold
                +mainWindow->HtmlColorMainAccent
                +QString::number(getVectorSize())
                +mainWindow->HtmlColorEnd
                +mainWindow->HtmlBoldEnd
                +" изображений");
    mainWindow->ui->label_c_currentImage->setText(
                "Изображение "
                +mainWindow->HtmlBold
                +mainWindow->HtmlColorMain
                +QString::number(getFileCounter()+1)
                +mainWindow->HtmlColorEnd
                +mainWindow->HtmlBoldEnd
                +" из "
                +mainWindow->HtmlBold
                +QString::number(getVectorSize())
                +mainWindow->HtmlBoldEnd);
}
