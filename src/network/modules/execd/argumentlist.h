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
    explicit ArgumentList(QObject *parent = nullptr);

    ExecdStringArgument* arg0 =  new ExecdStringArgument(this, "-f", "m1", "Имя файла");
    ExecdIntArgument* arg1 =     new ExecdIntArgument(this, "-m", 1, "Режим формирования");
    ExecdRealArgument* arg2 =    new ExecdRealArgument(this, "-t", 1, "Смещение по времени, с");
    ExecdIntArgument* arg3 =     new ExecdIntArgument(this, "-b", 0, "Яркость изображения");
    ExecdIntArgument* arg4 =     new ExecdIntArgument(this, "-e", 120, "Яркость изображения");
    ExecdStringArgument* arg5 =  new ExecdStringArgument(this, "-w", "HAMMING", "Оконная функция"); 
    ExecdIntArgument* arg6 =     new ExecdIntArgument(this, "-i", 0, "Интерполяция параметров скорости и высоты");    
    ExecdRealArgument* arg7 =    new ExecdRealArgument(this, "--Ts", 1, "Время синтезирования, с");     
    ExecdRealArgument* arg8 =    new ExecdRealArgument(this, "--Tstrip", 1, "Время полосовой съемки, с");     
    ExecdIntArgument* arg9 =     new ExecdIntArgument(this, "--kR", 1, "Коэффициент частотной интерполяции по дальности");    
    ExecdIntArgument* arg10 =    new ExecdIntArgument(this, "--kL", 1, "Коэффициент частотной интерполяции по путевой дальности");     
    ExecdIntArgument* arg11 =    new ExecdIntArgument(this, "--jq", 80, "Качество компрессии JPEG"); 

    ExecdRealArgument* arg12 =   new ExecdRealArgument(this, "--dx", 1, "Шаг по дальности, м");          
    ExecdRealArgument* arg13 =   new ExecdRealArgument(this, "--dy", 1, "Шаг по путевой дальности, м");          
    ExecdIntArgument* arg14 =    new ExecdIntArgument(this, "--x0", 100, "Ближняя граница по дальности");     
    ExecdIntArgument* arg15 =    new ExecdIntArgument(this, "--y0", 200);     
    ExecdIntArgument* arg16 =    new ExecdIntArgument(this, "--lx", 2000, "Дальняя граница по дальности");     
    ExecdIntArgument* arg17 =    new ExecdIntArgument(this, "--ly", 400);     
    ExecdStringArgument* arg18 = new ExecdStringArgument(this, "--ip", "./img/");        
    ExecdStringArgument* arg19 = new ExecdStringArgument(this, "--im", "out");        
    ExecdRealArgument* arg20 =   new ExecdRealArgument(this, "--Tshist", 1);          
    ExecdStringArgument* arg21 = new ExecdStringArgument(this, "--remote", "None", "Сервер для передачи данных [address:port]");        

signals:

};

#endif // ARGUMENTLIST_H
