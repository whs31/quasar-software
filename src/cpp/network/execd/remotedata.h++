#pragma once

#include <Definitions>
#include <QtCore/QObject>

namespace Network
{
    class RemoteData : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(float storageSpace READ storageSpace WRITE setStorageSpace NOTIFY storageSpaceChanged)

        public:
            explicit RemoteData(QObject* parent = nullptr);

            __getter float storageSpace() const;
            __setter void setStorageSpace(float other);

            signals:
                __signal storageSpaceChanged();

        private:
            float m_storageSpace = 0;
    };
} // namespace Network;
