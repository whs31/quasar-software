#include "tcpdebug.h"
#include "qlabel.h"
#include "ui_tcpdebug.h"

TCPDebug::TCPDebug(QWidget *parent, QPixmap pixmap) :
    QDialog(parent),
    ui(new Ui::TCPDebug)
{
    ui->setupUi(this);
    QLabel* pix = new QLabel(this);
    ui->mainLayout->addWidget(pix);
    pix->setPixmap(pixmap);
}

TCPDebug::TCPDebug(QWidget *parent, QStringList pathList) :
    QDialog(parent),
    ui(new Ui::TCPDebug)
{
    ui->setupUi(this);
    for(int i = 0; i < pathList.length(); i++)
    {
        QLabel* img = new QLabel(this);
        ui->mainLayout->addWidget(img);

        QPixmap _pixmap(pathList[i]);
        img->setPixmap(_pixmap);
    }
}

TCPDebug::~TCPDebug()
{
    delete ui;
}
