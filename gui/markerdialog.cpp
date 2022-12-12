#include "markerdialog.h"
#include "ui_markerdialog.h"

MarkerDialog::MarkerDialog(qreal latitude, qreal longitude, TMarker &marker) :
    newmarker(marker),
    ui(new Ui::MarkerDialog)
{
    ui->setupUi(this);
    ui->lineEdit_latitude->setText(QString::number(latitude));
    ui->lineEdit_longitude->setText(QString::number(longitude));
    ui->colorPicker->setColor(newmarker.color);
    ui->lineEdit_markerName->setText(newmarker.name);   
}

MarkerDialog::~MarkerDialog()
{
    //никогда не пытаться больше вызывать что-то в деструкторе. деструктор вызывается хер пойми когда (явно позже, чем нажимается кнопка Accept)
    //вместо этого мы обрабатываем такие действия в слоте кнопки accept/reject
    delete ui;
}

void MarkerDialog::on_buttonBox_accepted()
{
    newmarker.name = ui->lineEdit_markerName->text();
    newmarker.color = ui->colorPicker->getColor();
    newmarker.latitude = ui->lineEdit_latitude->text().toDouble();
    newmarker.longitude = ui->lineEdit_longitude->text().toDouble();
    newmarker.save = ui->checkBox_saveXML->isChecked();
    newmarker.scalable = !ui->checkBox_screenAnchor->isChecked();
    if(ui->radioButton_defaultMarker->isChecked())
    {
        newmarker.icon = MarkerIcon::GoogleDefaultMarker;
        //marker->anchorX =
        //marker->anchorY =
    } else if(ui->radioButton_flag->isChecked())
    {
        newmarker.icon = MarkerIcon::Flag;
        //marker->anchorX =
        //marker->anchorY =
    } else if(ui->radioButton_sar->isChecked())
    {
        newmarker.icon = MarkerIcon::SARImage;
        //marker->anchorX =
        //marker->anchorY =
    }
    done(QDialog::Accepted);
}

