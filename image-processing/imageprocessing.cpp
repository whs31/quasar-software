#include "imageprocessing.h"

ImageProcessing::ImageProcessing(QObject *parent) : QObject (parent)
{
    mainWindow = MainWindow::getMainWinPtr();
}

bool ImageProcessing::getReadyStatus()
{
    if(!imageList.empty()) { return 1; } return 0;
}

void ImageProcessing::decode(QStringList filelist)
{
    image_metadata metaStruct = {0,0,0,0,0,0,0,"error"};
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
                memcpy(&metaStruct, (data+JPEG_HEADER_SIZE+4), *metaSize);
                metaStruct.filename = fileName;
                QDateTime crDate = QFileInfo(_qfile).birthTime();
                metaStruct.datetime = crDate.toString("dd.MM в HH:mm:ss");

                qDebug()<<"[IMG] Decoded file ("<<filelist.indexOf(fileName)<<") successfully";
                metadataList.append(metaStruct);
            }

        } else { qDebug()<<"[IMG] Decoding error!"; }
    }
}

void ImageProcessing::processPath(QString path)
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
        qInfo()<<"[IMG] Imagelist fulfilled";
        imageList.clear();
        metadataList.clear();
        //qml clear and remove images =))))
        for ( QString f : fileList ) {
            imageList.append(f);
        }
    } else {
        QMessageBox warningDialogue;
        warningDialogue.setWindowTitle("Изображения не найдены!");
        warningDialogue.setIcon(QMessageBox::Warning);
        warningDialogue.setText("В выбранном каталоге не найдены изображения!");
        warningDialogue.exec();
    }
    decode(imageList);
    updateLabels(0);
    //showAllImages();
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
    mainWindow->ui->label_c_metaTime->setText(metadataList[structureIndex].datetime);
}

int ImageProcessing::getFileCounter()
{
    return fileCounter;
}

int ImageProcessing::getVectorSize()
{
    return imageList.length();
}
