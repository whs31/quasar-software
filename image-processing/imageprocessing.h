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

#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QObject>
#include <QtEndian>
#include <QImageReader>
#include <QMessageBox>
#include <QDateTime>

#include "imagemanager.h"
#include "linkerqml.h"

#include <QElapsedTimer>

#define JPEG_HEADER_SIZE 20
#define JPEG_CHECKSUM_SIZE 4

enum DecodeMode
{
    Initial,
    Partial
};

class ImageProcessing : public QObject
{
    Q_OBJECT
public:
    explicit ImageProcessing(LinkerQML* linker);
    bool InitialScan();
    bool PartialScan();
    bool getReadyStatus(void);
    int getFileCounter(void);
    int getVectorSize(void);
    void goLeft(void);
    void goRight(void);
    void showAllImages(bool showOnStart = false);
    void showPartialScanResult();
    void clearCache();

    QVector<bool> imageChecklist;

signals:
    void setLeftButton(bool b);
    void setRightButton(bool b);
    void updateTopLabels(int total, int current);
    void updateMetaLabels(QString filename, float lat, float lon, float dx, float dy, float x0, float y0, float angle, float driftAngle, QString hexSum, QString datetime, bool match);
    void enableImageBar(bool b);

private:
    LinkerQML* qmlLinker;
    ImageManager* imageManager;

    uint32_t getChecksum(const void* data, size_t length, uint32_t previousCrc32 = 0);
    void decode(QStringList filelist, DecodeMode mode = DecodeMode::Initial);
    void updateLabels(int structureIndex);
    QStringList getEntryList(QString &path);

    struct image_metadata {
            double latitude;
            double longitude;
            float dx;
            float dy;
            float x0;
            float y0;
            float angle;
            float driftAngle;
            uint32_t checksum;
            QString filename;
            QString datetime;
            bool checksumMatch;
            QString base64encoding;
        };
    QVector<image_metadata> metadataList;

    QStringList diff;
    bool notNull = false;
    short newImagesCounter = 0;
    int fileCounter = 0;
};

#endif // IMAGEPROCESSING_H
