#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QObject>
#include <QInputDialog>

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

private:
    Ui::SettingsDialog *uiS;
};

#endif // SETTINGSDIALOG_H
