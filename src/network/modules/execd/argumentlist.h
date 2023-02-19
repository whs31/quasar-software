#ifndef ARGUMENTLIST_H
#define ARGUMENTLIST_H

#include <QObject>
#include <QVector>

#include "execdargument.h"
#include "misc/debug.h"

class ArgumentList : public QObject
{
    Q_OBJECT
public:
    static ArgumentList* get(QObject* parent = nullptr);

    QString makeFormArguments(void);

    ExecdArgument* filename       =  new ExecdArgument(this, ArgumentType::String, "-f", "m1", "Имя файла");
    ExecdArgument* mode           =  new ExecdArgument(this, ArgumentType::Int, "-m", 1, "Режим формирования");
    ExecdArgument* timeshift      =  new ExecdArgument(this, ArgumentType::Float, "-t", 1, "Смещение по времени, с");
    ExecdArgument* brightness     =  new ExecdArgument(this, ArgumentType::Int, "-b", 0, "Яркость изображения");
    ExecdArgument* sealevel       =  new ExecdArgument(this, ArgumentType::Int, "--e0", 120, "Начальная высота в точке старта");
    ExecdArgument* elevation      =  new ExecdArgument(this, ArgumentType::Int, "-e", -1, "Текущая высота");
    ExecdArgument* velocity       =  new ExecdArgument(this, ArgumentType::Float, "-v", -1, "Текущая скорость");
    ExecdArgument* windowfunction =  new ExecdArgument(this, ArgumentType::String, "-w", "HAMMING", "Оконная функция");
    ExecdArgument* interpolation  =  new ExecdArgument(this, ArgumentType::Int, "-i", 0, "Интерполяция параметров скорости и высоты");
    ExecdArgument* time           =  new ExecdArgument(this, ArgumentType::Float, "--Ts", 1, "Время синтезирования, с");
    ExecdArgument* striptime      =  new ExecdArgument(this, ArgumentType::Float, "--Tstrip", 1, "Время полосовой съемки, с");
    ExecdArgument* freqinterp_x   =  new ExecdArgument(this, ArgumentType::Int, "--kR", 1, "Коэффициент частотной интерполяции по дальности");
    ExecdArgument* freqinterp_y   =  new ExecdArgument(this, ArgumentType::Int, "--kL", 1, "Коэффициент частотной интерполяции по путевой дальности");
    ExecdArgument* jpegcompression=  new ExecdArgument(this, ArgumentType::Int, "--jq", 80, "Качество компрессии JPEG");

    ExecdArgument* dx             =  new ExecdArgument(this, ArgumentType::Float, "--dx", 1, "Шаг по дальности, м");
    ExecdArgument* dy             =  new ExecdArgument(this, ArgumentType::Float, "--dy", 1, "Шаг по путевой дальности, м");
    ExecdArgument* x0             =  new ExecdArgument(this, ArgumentType::Int, "--x0", 100, "Ближняя граница по дальности");
    ExecdArgument* y0             =  new ExecdArgument(this, ArgumentType::Int, "--y0", 200);
    ExecdArgument* lx             =  new ExecdArgument(this, ArgumentType::Int, "--lx", 2000, "Дальняя граница по дальности");
    ExecdArgument* ly             =  new ExecdArgument(this, ArgumentType::Int, "--ly", 400);
    ExecdArgument* ip             =  new ExecdArgument(this, ArgumentType::String, "--ip", "./img/");
    ExecdArgument* im             =  new ExecdArgument(this, ArgumentType::String, "--im", "out");
    ExecdArgument* tshift2        =  new ExecdArgument(this, ArgumentType::Float, "--Tshift", 1);
    ExecdArgument* remote         =  new ExecdArgument(this, ArgumentType::String, "--remote", "None", "Сервер для передачи данных [address:port]");

    //ExecdArgument* rect_x         =  new ExecdArgument(this, ArgumentType::Float, "--px", "-1", "Сервер для передачи данных [address:port]");
    //ExecdArgument* rect_y         =  new ExecdArgument(this, ArgumentType::Float, "--py", "-1", "Сервер для передачи данных [address:port]");
    //ExecdArgument* rect_edge         =  new ExecdArgument(this, ArgumentType::Float, "--ls", "50", "Сервер для передачи данных [address:port]");
    //ExecdArgument* focus_vel_min         =  new ExecdArgument(this, ArgumentType::Float, "--vmin", "-1", "Сервер для передачи данных [address:port]");
    //ExecdArgument* focus_vel_max         =  new ExecdArgument(this, ArgumentType::Float, "--vmax", "-1", "Сервер для передачи данных [address:port]");
    //ExecdArgument* drift_angle         =  new ExecdArgument(this, ArgumentType::Float, "--driftAngle", "-1", "Сервер для передачи данных [address:port]");
    //ExecdArgument* focus_img_cnt=  new ExecdArgument(this, ArgumentType::Int, "--ni", "10", "Сервер для передачи данных [address:port]");
    // -v --Ts --ni --driftAngle -f --px --py --ls --vmin --vmax
    //$FOCUS( )



    //filename: xx_xxx no fileformat

signals:

private:
    static ArgumentList* _instance;
    explicit ArgumentList(QObject *parent = nullptr);
    QVector<ExecdArgument*> args;

};

#endif // ARGUMENTLIST_H
