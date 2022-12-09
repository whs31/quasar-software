#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include "style.h"

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr, QString softwareBuildVersion = "snapshot-1209");
    ~AboutDialog();

private:
    Ui::AboutDialog *ui;
    QString softwareVersion;
};

#endif // ABOUTDIALOG_H
