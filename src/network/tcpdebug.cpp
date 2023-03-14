#include "tcpdebug.h"
#include "ui_tcpdebug.h"

TCPDebug::TCPDebug(QWidget *parent, QPixmap pixmap) :
    QDialog(parent),
    ui(new Ui::TCPDebug)
{
    ui->setupUi(this);
    ui->img->setPixmap(pixmap);
}

TCPDebug::~TCPDebug()
{
    delete ui;
}
