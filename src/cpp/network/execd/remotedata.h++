#pragma once

#include <Definitions>
#include <QtCore/QObject>

namespace Network
{
    class RemoteData : public QObject
    {
        Q_OBJECT
        PROPERTY_DEF(float, storageSpace, setStorageSpace, m_storageSpace)

        public:
            explicit RemoteData(QObject* parent = nullptr);

            signals:
                __property_signal storageSpaceChanged();

        private:
            float m_storageSpace = 0;
    };
} // namespace Network;
