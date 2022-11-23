#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QObject>
#include <QStandardPaths>
#include <QFileDialog>

#include "sconfig.h"


namespace Ui {
class SettingsDialog;
}
class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

signals:

private slots:
    void on_pushButton_clicked();
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::SettingsDialog *uiS;
};

#endif // SETTINGSDIALOG_H
