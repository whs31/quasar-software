#include "markerdialog.h"
#include "ui_markerdialog.h"
#include <QDebug>

MarkerDialog::MarkerDialog(qreal latitude, qreal longitude, Marker &marker) :
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
    newmarker.setColor(MarkerColor::Brown);
    newmarker.latitude = ui->lineEdit_latitude->text().toDouble();
    newmarker.longitude = ui->lineEdit_longitude->text().toDouble();
    newmarker.save = ui->checkBox_saveXML->isChecked();
    newmarker.setScalable(!ui->checkBox_screenAnchor->isChecked());
    if(ui->radioButton_defaultMarker->isChecked())
    {
        newmarker.setIcon(MarkerIcon::Default);
    } else if(ui->radioButton_flag->isChecked())
    {
        newmarker.setIcon(MarkerIcon::Flag);
    } else if(ui->radioButton_sar->isChecked())
    {
        newmarker.setIcon(MarkerIcon::Radar);
    }
    if(newmarker.autocapture)
    {
        newmarker.setIcon(MarkerIcon::Target);
        newmarker.setColor(MarkerColor::Red);
    }
    done(QDialog::Accepted);
}


void MarkerDialog::on_checkBox_autocapture_clicked(bool checked)
{
    ui->colorPicker->setEnabled(!checked);
    ui->checkBox_saveXML->setEnabled(!checked);
    ui->checkBox_screenAnchor->setEnabled(!checked);
    ui->radioButton_defaultMarker->setEnabled(!checked);
    ui->radioButton_flag->setEnabled(!checked);
    ui->radioButton_sar->setEnabled(!checked);
    ui->horizontalLayout->setEnabled(!checked);
    ui->scrollArea->setEnabled(!checked);
    newmarker.autocapture = checked;
    ui->lineEdit_markerName->setText(checked ? "Цель для автозахвата" : "Новый маркер");
}

