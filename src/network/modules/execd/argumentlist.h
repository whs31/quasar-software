#ifndef ARGUMENTLIST_H
#define ARGUMENTLIST_H

#include <QObject>

#include "execdintargument.h"
#include "execdrealargument.h"
#include "execdstrargument.h"
#include "misc/debug.h"

class ArgumentList : public QObject
{
    Q_OBJECT
public:
    static ArgumentList* get(QObject* parent = nullptr);

    QString makeFormArguments(void);

    ExecdStringArgument* filename       =  new ExecdStringArgument(this, "-f", "m1", "Имя файла");
    ExecdIntArgument* mode              =  new ExecdIntArgument(this, "-m", 1, "Режим формирования");
    ExecdRealArgument* timeshift        =  new ExecdRealArgument(this, "-t", 1, "Смещение по времени, с");
    ExecdIntArgument* brightness        =  new ExecdIntArgument(this, "-b", 0, "Яркость изображения");
    ExecdIntArgument* sealevel          =  new ExecdIntArgument(this, "-e", 120, "Начальная высота в точке старта");
    ExecdStringArgument* windowfunction =  new ExecdStringArgument(this, "-w", "HAMMING", "Оконная функция");
    ExecdIntArgument* interpolation     =  new ExecdIntArgument(this, "-i", 0, "Интерполяция параметров скорости и высоты");
    ExecdRealArgument* time             =  new ExecdRealArgument(this, "--Ts", 1, "Время синтезирования, с");
    ExecdRealArgument* striptime        =  new ExecdRealArgument(this, "--Tstrip", 1, "Время полосовой съемки, с");
    ExecdIntArgument* freqinterp_x      =  new ExecdIntArgument(this, "--kR", 1, "Коэффициент частотной интерполяции по дальности");
    ExecdIntArgument* freqintep_y       =  new ExecdIntArgument(this, "--kL", 1, "Коэффициент частотной интерполяции по путевой дальности");
    ExecdIntArgument* jpegcompression   =  new ExecdIntArgument(this, "--jq", 80, "Качество компрессии JPEG");

    ExecdRealArgument* dx               =  new ExecdRealArgument(this, "--dx", 1, "Шаг по дальности, м");
    ExecdRealArgument* dy               =  new ExecdRealArgument(this, "--dy", 1, "Шаг по путевой дальности, м");
    ExecdIntArgument* x0                =  new ExecdIntArgument(this, "--x0", 100, "Ближняя граница по дальности");
    ExecdIntArgument* y0                =  new ExecdIntArgument(this, "--y0", 200);
    ExecdIntArgument* lx                =  new ExecdIntArgument(this, "--lx", 2000, "Дальняя граница по дальности");
    ExecdIntArgument* ly                =  new ExecdIntArgument(this, "--ly", 400);
    ExecdStringArgument* ip             =  new ExecdStringArgument(this, "--ip", "./img/");
    ExecdStringArgument* im             =  new ExecdStringArgument(this, "--im", "out");
    ExecdRealArgument* tshift2          =  new ExecdRealArgument(this, "--Tshift", 1);
    ExecdStringArgument* remote         =  new ExecdStringArgument(this, "--remote", "None", "Сервер для передачи данных [address:port]");

signals:

private:
    static ArgumentList* _instance;
    explicit ArgumentList(QObject *parent = nullptr);

};

#endif // ARGUMENTLIST_H
