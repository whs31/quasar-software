#ifndef STEXT_H
#define STEXT_H

#include <QObject>
#include <QColor>

class SText : public QObject
{
    Q_OBJECT
public:
    explicit SText(QObject *parent = nullptr);

    static QString localNumeralEnding(int numeral);
    Q_INVOKABLE static QString colorText(QString text, QColor color);

signals:

};

#endif // STEXT_H
