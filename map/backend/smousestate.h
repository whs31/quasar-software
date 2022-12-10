#ifndef SMOUSESTATE_H
#define SMOUSESTATE_H

#include <QObject>

enum MouseState : short int
{
    Blank,
    MarkerPlacement
};

class SMouseState : public QObject
{
    Q_OBJECT
public:
    explicit SMouseState(QObject *parent = nullptr);
    static short int mouseState;

signals:

};

#endif // SMOUSESTATE_H
