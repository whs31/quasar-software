#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>
#include <QObject>
#include <QMap>

#define group_t QMap<QString,QString>
#define checkValuesSimple(X) checkValues(#X, &X)

class Config : public QSettings
{
    Q_OBJECT
public:
    Config(QString fn = "default.cfg");

private:
    void checkValues(QString group, group_t *list);

};

#endif // CONFIG_H
