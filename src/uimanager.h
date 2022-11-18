#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "mainwindow.h"
#include "htmltags.h"

class UIManager : public QObject
{
    Q_OBJECT
public:
    UIManager(MainWindow* w);
    MainWindow* w;
};

#endif // UIMANAGER_H
