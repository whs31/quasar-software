#include "markerdialog.h"
#include "ui_markerdialog.h"

MarkerDialog::MarkerDialog(qreal latitude, qreal longitude, TMarker* marker) :
    marker(marker),
    ui(new Ui::MarkerDialog)
{
    ui->setupUi(this);
    ui->lineEdit_latitude->setText(QString::number(latitude));
    ui->lineEdit_longitude->setText(QString::number(longitude));
    ui->colorPicker->setColor(marker->color);
    ui->lineEdit_markerName->setText(marker->name);
}

MarkerDialog::~MarkerDialog()
{
    marker->name = ui->lineEdit_markerName->text();
    marker->color = ui->colorPicker->getColor();
    marker->latitude = ui->lineEdit_latitude->text().toDouble();
    marker->longitude = ui->lineEdit_longitude->text().toDouble();
    marker->save = ui->checkBox_saveXML->isChecked();
    marker->scalable = ui->checkBox_screenAnchor->isChecked();
    if(ui->radioButton_defaultMarker->isChecked())
    {
        marker->icon = MarkerIcon::GoogleDefaultMarker;
        //marker->anchorX =
        //marker->anchorY =
    } else if(ui->radioButton_flag)
    {
        marker->icon = MarkerIcon::Flag;
        //marker->anchorX =
        //marker->anchorY =
    } else if(ui->radioButton_sar)
    {
        marker->icon = MarkerIcon::SARImage;
        //marker->anchorX =
        //marker->anchorY =
    }
    delete ui;
}
