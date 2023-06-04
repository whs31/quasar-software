#include "execdargumentlist.h"
#include <QtCore/QVariant>

namespace Network
{

ExecdArgument::ExecdArgument()
    : value("Error")
    , type(String)
{}

ExecdArgument::ExecdArgument(int i)
    : value(QString::number(i))
    , type(Integer)
{}

ExecdArgument::ExecdArgument(float f)
    : value(QString::number(f, 'f', FLOATING_POINT_PRECISION))
    , type(Float)
{}

ExecdArgument::ExecdArgument(QString s)
    : value(s)
    , type(String)
{}

void ExecdArgument::set(const QVariant& v)
{
    switch (type)
    {
        case Float: value = QString::number(v.toFloat(), 'f', FLOATING_POINT_PRECISION); break;
        case Integer: value = QString::number(v.toInt()); break;
        case String: value = v.toString(); break;
        default: break;
    }
}

ExecdArgumentList::ExecdArgumentList(QObject* parent)
    : QObject{parent}
{

}

} // Network
