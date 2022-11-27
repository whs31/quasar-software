/* <Класс ImageProcessing : QObject>
 *      Первый класс для работы с радиолокационными изображениями.
 *      Данный класс работает со списками РЛИ, декодированием метадан-
 *      ных и отображением полученных РЛИ на карте. Для работы с файлами
 *      используется класс ImageManager.
 *
 *•Публичные методы:
 *      ► bool InitialScan()
 *
 *        Выполняет полное сканирование рабочей директории. Рабочая директория
 *        задается классом SConfig и зависит от использования загрузчика изобра-
 *        жений. Декодирует, обрабатывает и выводит все найденные изображения
 *        на карту QML.
 *
 *      ► bool PartialScan()
 *
 *        Выполняет частичное сканирование рабочей директории. Рабочая директория
 *        задается классом SConfig и зависит от использования загрузчика изобра-
 *        жений. Работает только с теми изображениями, которые есть в рабочей
 *        директории, но отсутствуют в интерфейсе и на карте. Декодирует, обраба-
 *        тывает и выводит все найденные отличающиеся изображения на карту QML.
 *
 *      ► bool getReadyStatus()
 *
 *        Возвращает статус менеджера изображений. Возвращает true, если поиск
 *        изображений в рабочей директории завершился.
 *
 *      ► int getFileCounter();
 *
 *        Возвращает индекс изображения в списке, которое сейчас отображается в
 *        интерфейсе программы и над которым производятся действия пользователем.
 *
 *      ► int getVectorSize(void);
 *
 *        Возвращает полное количество изображений в списке.
 *
 *      ► void goLeft(void);
 *
 *        Смещает индекс изображения в списке, которое сейчас отображается и над
 *        которым пользователь может производить действия, вниз по списку на 1. Не
 *        смещает, если данное изображение - первое в списке.
 *
 *      ► void goRight(void);
 *
 *        Смещает индекс изображения в списке, которое сейчас отображается и над
 *        которым пользователь может производить действия, вверх по списку на 1. Не
 *        смещает, если данное изображение - последнее в списке.
 *
 *      ► void clearCache();
 *
 *        Очищает кэш программы, список изображений и все изображения на карте. Создает
 *        новый кэш и выполняет полное сканирование рабочей директории.
 *
 *•Публичные члены класса:
 *      ► QVector<bool> imageChecklist
 *
 *        Список булевых переменных для работы с интерфейсом программы. Редактируется
 *        интерфейсом извне.
 *
 *•Сигналы:
 *      ► setLeftButton(bool b);
 *
 *        Задает состояние кнопки перемещения вниз по списку изображений. Сигнал подается,
 *        когда требуется это изменение.
 *
 *      ► setRightButton(bool b)
 *
 *        Задает состояние кнопки перемещения вверх по списку изображений. Сигнал подается,
 *        когда требуется это изменение.
 *
 *      ► updateTopLabels(int total, int current)
 *
 *        Сигнал для обновления верхней панели интерфейса РЛИ. Задает текущее рабочее
 *        изображение и общее количество изображениий в списке.
 *
 *      ► updateMetaLabels(QString filename, float lat, float lon, float dx, float dy, float x0, float y0, float angle, float driftAngle, QString hexSum, QString datetime, bool match)
 *
 *        Сигнал для обновления панели метаданных в интерфейсе РЛИ. Задает все метаданные
 *        текущего изображения и подается при изменении индекса текущего изображения либо
 *        при сканировании рабочей директории.
 *
 *      ► enableImageBar(bool b)
 *
 *        Сигнал для отображения панели для работы с РЛИ в интерфейсе. Включает панель, если
 *        есть хотя бы одно действительное изображение в списке и выключает, если их нет.
*/

#include "imageprocessing.h"

ImageProcessing::ImageProcessing(LinkerQML* linker) : qmlLinker(linker)
{
    imageManager = new ImageManager;
}

bool ImageProcessing::getReadyStatus()
{
    if(!metadataList.empty())
    {
        return 1;
    } return 0;
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
            qDebug()<<"[FILEMANAGER] Metadata list contains "<<strl.length()<<" files";
        /*
         *          отрезаем формат, путь уже отрезан entryList(). Получается, str = имя файла без указания формата и пути к нему (mx_xx-xx-xxxx_xx-xx-xx)
         *          аналогичное действие должен провернуть метод ImageManager getDiff(), чтобы сравнивать конкретно имена файлов без расширений и путей.
         */
        for (int i = 0; i<strl.length(); i++) { strl[i].chop(4); }
        return strl;
    } else {
        qDebug()<<"[FILEMANAGER] Metadata list contains zero files, calling ImageManager...";
        return {};
    }
}

bool ImageProcessing::InitialScan() //recall after changing settings
{
    QString initialPath = (SConfig::USELOADER) ? SConfig::CACHEPATH : SConfig::PATH;
    diff.clear();
    diff = imageManager->GetDiff(getEntryList(initialPath));

    QStringList imageList = imageManager->GetInitialList(initialPath, diff);

    if(!diff.empty())
    {
        qInfo()<<"[FILEMANAGER] Diff: "<<diff.length()<<" files";
    } else {
        qInfo()<<"[FILEMANAGER] No difference between cache and path found. Image processing will be skipped";
    }
    if(!imageList.empty())
    {
        notNull = true;
        qInfo()<<"[IMG] Imagelist fulfilled";

        metadataList.clear();
        qmlLinker->clearImageArray();

        decode(imageList, DecodeMode::Initial);
        updateLabels(0);

        emit updateTopLabels(getVectorSize(), getFileCounter());
    } else {
        notNull = false;
        qDebug()<<"[IMG] Directory is empty, throwing warning window...";
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
        showAllImages(SConfig::SHOWIMAGEONSTART);
    }
    emit enableImageBar(notNull);
    return notNull;
}

bool ImageProcessing::PartialScan()
{
    QString initialPath = (SConfig::USELOADER) ? SConfig::CACHEPATH : SConfig::PATH;
    bool foundNew = false;
    diff.clear();
    diff = imageManager->GetDiff(getEntryList(initialPath));

    QStringList imageList = imageManager->GetPartialList(initialPath, diff);
    if(!diff.empty())
    {
        qInfo()<<"[FILEMANAGER] Diff: "<<diff.length()<<" files";
    } else {
        qInfo()<<"[FILEMANAGER] Partial scan found no difference to process";
    }
    if(!imageList.empty())
    {
        qInfo()<<"[IMG] Imagelist fulfilled";
        foundNew = true;
        notNull = true;
        if(getVectorSize()>1)
        {
            emit(setRightButton(true));
        }
        emit enableImageBar(true);
        decode(imageList, DecodeMode::Partial);

        emit updateTopLabels(getVectorSize(), getFileCounter());
    } else {
        qDebug()<<"[IMG] Partial scan found no images to process";
        foundNew = false;
    }
    if(foundNew)
    {
        emit(setRightButton(true));
    }
    if(getReadyStatus())
    {
        for(int i = getVectorSize()-newImagesCounter; i<getVectorSize(); i++)
        {
            imageChecklist.append(SConfig::SHOWIMAGEONSTART);
        }
        showPartialScanResult();
    }
    return foundNew;
}

void ImageProcessing::decode(QStringList filelist, DecodeMode mode)
{
    image_metadata metaStruct = {0,0,0,0,0,0,0,0,0,"-", "-", false, "-"};
    qDebug()<<"[IMG] Called decoding function for image from filelist of "<<filelist.length()<<" files";
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
                metaStruct.checksumMatch = 0; //(newChecksum==metaStruct.checksum) ? 1 : 0;

                //создание маски альфа-канала
                QImageReader reader(metaStruct.filename);
                QSize sizeOfImage = reader.size();
                int height = sizeOfImage.height();
                int width = sizeOfImage.width();
                if(SConfig::USEBASE64)
                {
                    qInfo()<<"[IMG] Using base64 encoding, making mask...";
                    metaStruct.base64encoding = imageManager->addAlphaMask(metaStruct.filename, width, height, 13, 30, 0, 0, MaskFormat::Geometric);
                    if(metaStruct.base64encoding.length()<100)
                    {
                        qCritical()<<"[IMG] Something went wrong (base64) "<<metaStruct.base64encoding;
                    }
                }
                else if(!diff.empty()&&ImageManager::diffConvert(diff, ImageFormat::JPEG).contains(info.fileName()))
                {
                    qDebug()<<"[IMG] Using saving to disk, making mask...";
                    imageManager->addAlphaMask(metaStruct.filename, width, height, 13, 30, 0, 0, MaskFormat::Geometric);
                }
                metadataList.append(metaStruct);
                if(mode == DecodeMode::Partial)
                {
                    newImagesCounter++;
                }
            } else {
                qCritical()<<"[IMG] Marker error!";
            }
        } else {
            qCritical()<<"[IMG] Decoding error!";
        }
    }
}

void ImageProcessing::updateLabels(int structureIndex)
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

            qmlLinker->addImage(meta.latitude, meta.longitude, meta.dx, meta.dy, meta.x0, meta.y0, meta.angle, meta.filename, sizeOfImage.height(), meta.base64encoding);

            if(meta.base64encoding.length()<100 && SConfig::USEBASE64)
            {
                qCritical()<<"[QML] Something went wrong";
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
    qInfo()<<"[IMG] Initial images shown successfully";
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
                                    metadataList[metadataList.length()-i].angle, metadataList[metadataList.length()-i].filename,
                                    sizeOfImage.height(), metadataList[metadataList.length()-i].base64encoding);

                if(metadataList[metadataList.length()-i].base64encoding.length()<100 && SConfig::USEBASE64)
                {
                    qCritical()<<"[QML] Something went wrong";
                }
            }
        }
        qInfo()<<"[IMG] Some new images shown successfully";
        newImagesCounter = 0;
    } else {
        qWarning()<<"[IMG] No new images, skipping qml part";
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
        updateLabels(fileCounter);
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
        fileCounter++; updateLabels(fileCounter);
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
