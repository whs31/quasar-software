#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), uiS(new Ui::SettingsDialog)
{
    uiS->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete uiS;
}
