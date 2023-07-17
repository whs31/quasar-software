/**
 * \ingroup sdk_network
 * \class QuasarSDK::OutputSocket COutputSocket.h <QuasarSDK/Networking/COutputSocket.h>
 * \brief Сокет для приема и обработки вывода с РЛС.
 * \details Класс принимает стандартный вывод с РЛС и
 * предоставляет его для класса OutputRedirectServer и для
 * парсера VT100 (не входит в SDK). Также класс ищет ключевые
 * последовательности, такие как информация о свободном месте на диске,
 * и выбрасывает сигнал с обработанными данными.
 * \note Класс не предоставляет стандартные отладочные метрики.
 * \extends BaseUDPSocket
 */

#include "COutputSocket.h"
#include "CConfig.h"

namespace QuasarSDK
{
  OutputSocket::OutputSocket(QObject* parent)
      : BaseUDPSocket(parent)
  {
    this->setName("Feedback");
    connect(this, &OutputSocket::received, this, &OutputSocket::process, Qt::DirectConnection);
  }

  void OutputSocket::process(QByteArray data) noexcept
  {
    try
    {
      QString dataString = data;
      if(dataString.contains(Config::get()->value<QString>("STDOUT_STORAGE_STATUS")))
      {
        dataString.remove(Config::get()->value<QString>("STDOUT_STORAGE_STATUS"));
        dataString.remove(0, 1);

        qDebug().noquote() << "[SAR] Received storage status: " << dataString;

        emit diskSpaceReceived(dataString.split(' ', Qt::SkipEmptyParts).first().toLong(),
                               dataString.split(' ', Qt::SkipEmptyParts).last().toLong());
      }
    }
    catch(...)
    {
      qCritical() << "[FEEDBACK] Exception at parsing result";
    }
  }
} // QuasarSDK