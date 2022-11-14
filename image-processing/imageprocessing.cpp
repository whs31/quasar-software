#include "imageprocessing.h"

ImageProcessing::ImageProcessing(QObject *parent) : QObject (parent)
{
    mainWindow = MainWindow::getMainWinPtr();
}

ImageProcessing::image_metadata ImageProcessing::decode(QString path)
{
    image_metadata metaStruct = {0,0,0,0,0,0,0,"err"};
    qDebug()<<"[IMG] Called decoding function for image from "<<path;
    QFile _qfile(path);
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
            metaStruct.filename = path;
            qDebug()<<"[IMG] Decoded file ("<<metaStruct.filename<<") successfully";
        }
        return metaStruct;
    } else { qDebug()<<"[IMG] Decoding error!"; return metaStruct; } //.filename = err failcheck
}
