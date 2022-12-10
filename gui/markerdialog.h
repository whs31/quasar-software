#ifndef MARKERDIALOG_H
#define MARKERDIALOG_H

#include <QDialog>

namespace Ui {
class MarkerDialog;
}

class MarkerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MarkerDialog(QWidget *parent = nullptr);
    ~MarkerDialog();

private:
    Ui::MarkerDialog *ui;
};

#endif // MARKERDIALOG_H
