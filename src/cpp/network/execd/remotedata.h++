#pragma once

#include <definitions.h++>
#include <QtCore/QObject>

namespace Network
{
    class RemoteData : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(float storageSpace READ storageSpace WRITE setStorageSpace NOTIFY storageSpaceChanged)

        float m_storageSpace = 0;

        public:
            explicit RemoteData(QObject* parent = nullptr);

            float storageSpace() const;
            void setStorageSpace(float other);

            signals:
                __signal storageSpaceChanged();
    };
} // namespace Network;
