/**
 *  \file quasarsdk_pingtester.h
 *  \author Дмитрий Рязанцев
 *  \date 05.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <QtCore/QObject>
#include <QtCore/QStringList>
#include "public/quasarsdk_enums.h"

class QProcess;

namespace QuasarSDK
{
  class PingTester : public QObject
  {
    Q_OBJECT

    public:
      explicit PingTester(QObject* parent = nullptr);
      ~PingTester() override;

      void start(const QString& address, const QStringList& args);
      void stop() noexcept;

    signals:
      /**
       * \brief Сигнал предоставляет результат выполнения команды \c ping.
       * \param res - статус-код.
       */
      void result(Enums::PingStatus res);

    private:
      Q_SLOT void ping();
      Q_SLOT void recv();

    private:
      QProcess* m_process;
      QString m_address;
      QStringList m_args;
  };
} // QuasarSDK
