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
    const int max_columns = 8;
    int columns = 0;
    int rows = 0;
    for(int i = 0; i < pathList.length(); i++)
    {
        if(pathList[i].contains("e.jpg"))
            continue;
        QLabel* img = new QLabel(this);

        ui->mainLayout->addWidget(img, rows, columns);
        if(columns < max_columns)
            columns++;
        else
        {
            columns = 0;
            rows++;
        }
        QPixmap _pixmap(pathList[i]);

        img->setPixmap(_pixmap.scaled(64, 64, Qt::KeepAspectRatio));
        img->setToolTip(pathList[i]);
        this->adjustSize();
    }
}

TCPDebug::~TCPDebug()
{
    delete ui;
}
