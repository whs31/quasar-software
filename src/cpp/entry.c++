#include "entry.h++"
#include "gui/theme/include/theme.h++"
#include "config/paths.h++"

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtQml/qqml.h>

Entry::Entry(QObject *parent)
    : QObject{parent}
{
    qmlRegisterSingletonInstance<Config::Paths>("Path", 1, 0, "Path", Config::Paths::get(this));
    qmlRegisterSingletonInstance<GUI::Theme>("Theme", 1, 0, "Theme", GUI::Theme::get(this));
}
