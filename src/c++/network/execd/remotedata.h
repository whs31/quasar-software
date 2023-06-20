#pragma once

#include <QtCore/QObject>
#include "network/netenums.h"

namespace Networking
{
    class RemoteData : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(float storageSpace READ storageSpace WRITE setStorageSpace NOTIFY storageSpaceChanged)
        Q_PROPERTY(int de10ping READ de10ping WRITE setDe10ping NOTIFY de10pingChanged)
        Q_PROPERTY(int jetsonping READ jetsonping WRITE setJetsonping NOTIFY jetsonpingChanged)
        Q_PROPERTY(int navping READ navping WRITE setNavping NOTIFY navpingChanged)
        Q_PROPERTY(int utl1ping READ utl1ping WRITE setUtl1ping NOTIFY utl1pingChanged)
        Q_PROPERTY(int utl2ping READ utl2ping WRITE setUtl2ping NOTIFY utl2pingChanged)

        public:
            explicit RemoteData(QObject* parent = nullptr);

            float storageSpace() const; void setStorageSpace(float);

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
