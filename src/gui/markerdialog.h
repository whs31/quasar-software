#ifndef MARKERDIALOG_H
#define MARKERDIALOG_H

#include <QDialog>

#include "map/models/tmarker.h"

namespace Ui {
class MarkerDialog;
}

class MarkerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MarkerDialog(qreal latitude, qreal longitude, TMarker& marker);
    ~MarkerDialog();


private slots:
    void on_buttonBox_accepted();

    void on_checkBox_autocapture_clicked(bool checked);

private:
    Ui::MarkerDialog *ui;
    TMarker& newmarker;
};

#endif // MARKERDIALOG_H
