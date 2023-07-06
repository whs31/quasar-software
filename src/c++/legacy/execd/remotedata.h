/**
 *  \file remotedata.h
 *  \author Dmitry Ryazancev
 *  \date 30.06.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <QtCore/QObject>
#include "network/netenums.h"

namespace Networking
{
  /**
  * \brief Class for storing SAR-related data.
  * \details Class is used to store different SAR-related
  * data fields and provide access to it to QML engine.
  * \extends QObject
  */
  class RemoteData : public QObject
  {
      /**
       * \property storageSpace
       * \brief Remote storage status (normalized percentage).
       * \par %storageSpace, setStorageSpace, storageSpaceChanged
       *
       * \property de10ping
       * \brief Ping status for DE10 module as #Enums::PingStatus.
       * \par %de10ping, setDe10ping, de10pingChanged
       *
       * \property jetsonping
       * \brief Ping status for Jetson module as #Enums::PingStatus.
       * \par %jetsonping, setJetsonping, jetsonpingChanged
       *
       * \property navping
       * \brief Ping status for navigation module as #Enums::PingStatus.
       * \par %navping, setNavping, navpingChanged
       *
       * \property utl1ping
       * \brief Ping status for antenna commutator module as #Enums::PingStatus.
       * \par %utl1ping, setUtl1ping, utl1pingChanged
       *
       * \property utl2ping
       * \brief Ping status for power commutator module as #Enums::PingStatus.
       * \par %utl2ping, setUtl2ping, utl2pingChanged
       */

    Q_OBJECT
      Q_PROPERTY(float storageSpace READ storageSpace WRITE setStorageSpace NOTIFY storageSpaceChanged)
      Q_PROPERTY(int de10ping READ de10ping WRITE setDe10ping NOTIFY de10pingChanged)
      Q_PROPERTY(int jetsonping READ jetsonping WRITE setJetsonping NOTIFY jetsonpingChanged)
      Q_PROPERTY(int navping READ navping WRITE setNavping NOTIFY navpingChanged)
      Q_PROPERTY(int utl1ping READ utl1ping WRITE setUtl1ping NOTIFY utl1pingChanged)
      Q_PROPERTY(int utl2ping READ utl2ping WRITE setUtl2ping NOTIFY utl2pingChanged)

    public:
      /// \brief Constructs new RemoteData object with given parent.
      explicit RemoteData(QObject* parent = nullptr);

      [[nodiscard]] float storageSpace() const; void setStorageSpace(float);
      [[nodiscard]] int de10ping() const; void setDe10ping(int);
      [[nodiscard]] int jetsonping() const; void setJetsonping(int);
      [[nodiscard]] int navping() const; void setNavping(int);
      [[nodiscard]] int utl1ping() const; void setUtl1ping(int);
      [[nodiscard]] int utl2ping() const; void setUtl2ping(int);

    signals:
      void storageSpaceChanged();
      void de10pingChanged();
      void jetsonpingChanged();
      void navpingChanged();
      void utl1pingChanged();
      void utl2pingChanged();

    private:
      float m_storageSpace;
      int m_de10ping;
      int m_jetsonping;
      int m_navping;
      int m_utl1ping;
      int m_utl2ping;
  };
} // namespace Network;
