/**
 *  \file quasarsdk_tcpserver.h
 *  \author Дмитрий Рязанцев
 *  \date 05.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <QtCore/QObject>

class QTcpServer;
class QTcpSocket;
class QTimer;

namespace QuasarSDK
{
  class TCPServer : public QObject
  {
    Q_OBJECT

    public:
      explicit TCPServer(QObject* parent = nullptr);

      void start(const QString& address) noexcept;
      void stop() noexcept;

    signals:
      /**
       * \brief Срабатывает, когда сервер завершает прием данных от клиента.
       * \param data - массив байт с данными.
       */
      void received(QByteArray data);

      /**
       * \brief Срабатывает во время изменения прогресса загрузки файла.
       * \param progress - процент загрузки (от 0 до 100).
       */
      void progressChanged(float progress);

      /// \brief Отладочные метрики сокета, аналогичные BaseUDPSocket::metrics.
      void metrics(const QString& data, int size_bytes, bool out);

    private:
      void (TCPServer::*readFile)(QByteArray data);
      void readFileInfo(QByteArray data);
      void readFileBody(QByteArray data);
      void progress();

      Q_SLOT void clientConnected();
      Q_SLOT void serverRead();
      Q_SLOT void clientDisconnected();
      Q_SLOT void connectionTimeout();

    private:
      QTcpServer* server;
      QTcpSocket* socket;
      QTimer* timer;
      QByteArray imageData;

      bool success = false;
      uint8_t splitIndex;
      uint32_t fileSize;
      QString filename;
  };
} // QuasarSDK
