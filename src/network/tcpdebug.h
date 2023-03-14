#ifndef TCPDEBUG_H
#define TCPDEBUG_H

#include <QDialog>
#include <QPixmap>

namespace Ui {
class TCPDebug;
}

class TCPDebug : public QDialog
{
    Q_OBJECT

public:
    explicit TCPDebug(QWidget *parent = nullptr, QPixmap pixmap = QPixmap());
    ~TCPDebug();

private:
    Ui::TCPDebug *ui;
};

#endif // TCPDEBUG_H
