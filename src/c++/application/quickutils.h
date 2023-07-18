//
// Created by whs31 on 18.07.23.
//

#pragma once
#include <QtCore/QObject>

namespace Application
{
  class QuickUtils : public QObject
  {
    Q_OBJECT

    public:
      explicit QuickUtils(QObject* parent = nullptr);

      Q_INVOKABLE static QString currentDateString();
  };
} // Application
