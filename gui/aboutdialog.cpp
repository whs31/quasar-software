#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent, QString softwareBuildVersion) :
    QDialog(parent),
    softwareVersion(softwareBuildVersion),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    //regex to detect stable
    //also change in debug logs and remove from config software version
    ui->softVersion->setText(Style::StyleText(softwareVersion, Colors::Accent100, Format::Bold));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
