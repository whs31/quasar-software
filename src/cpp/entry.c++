#include "entry.h++"
#include "gui/theme/include/theme.h++"

#include <QCoreApplication>
#include <QDebug>
#include <qqml.h>

Entry::Entry(QObject *parent)
    : QObject{parent}
{
    qmlRegisterSingletonInstance<GUI::Theme>("Theme", 1, 0, "Theme", GUI::Theme::get(this));
}
