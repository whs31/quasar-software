#ifndef TCPDEBUG_H
#define TCPDEBUG_H

#include <QDialog>
#include <QPixmap>
#include <QStringList>

namespace Ui {
class TCPDebug;
}

class TCPDebug : public QDialog
{
    Q_OBJECT

public:
    explicit TCPDebug(QWidget *parent = nullptr, QPixmap pixmap = QPixmap());
    explicit TCPDebug(QWidget *parent = nullptr, QStringList pathList = {});
    ~TCPDebug();

private:
    Ui::TCPDebug *ui;
};

#endif // TCPDEBUG_H
