#ifndef STEXT_H
#define STEXT_H

#include <QObject>

class SText : public QObject
{
    Q_OBJECT
public:
    explicit SText(QObject *parent = nullptr);

    static QString localNumeralEnding(int numeral);

signals:

};

#endif // STEXT_H
