#ifndef MARKERDIALOG_H
#define MARKERDIALOG_H

#include <QDialog>
#include "models/tmarker.h"

namespace Ui {
class MarkerDialog;
}

class MarkerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MarkerDialog(qreal latitude, qreal longitude, TMarker* marker);
    ~MarkerDialog();


private:
    Ui::MarkerDialog *ui;
    TMarker* marker;
};

#endif // MARKERDIALOG_H
