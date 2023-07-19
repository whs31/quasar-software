//
// Created by whs31 on 18.07.23.
//

#include "quickutils.h"
#include <QtCore/QDateTime>

namespace Application
{
  QuickUtils::QuickUtils(QObject* parent)
    : QObject(parent)
  {}

  QString QuickUtils::currentDateString() { return QDateTime::currentDateTime().toString("dd-MM-yyyy_hh-mm-ss"); }
} // Application