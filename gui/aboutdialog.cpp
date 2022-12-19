#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent, QString softwareBuildVersion) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->softVersion->setText(Style::StyleText(softwareBuildVersion, softwareBuildVersion.contains("-") ? Colors::Accent100 : Colors::Info100, Format::Bold));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
