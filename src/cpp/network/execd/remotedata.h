#pragma once

#include <QtCore/QObject>
#include <ccl/ccl_global.h>

namespace Network
{
    class RemoteData : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(float storageSpace READ storageSpace WRITE setStorageSpace NOTIFY storageSpaceChanged)

        public:
            explicit RemoteData(QObject* parent = nullptr);

            float storageSpace() const; void setStorageSpace(float);

            signals:
                void storageSpaceChanged();

        private:
            float m_storageSpace = 0;
    };
} // namespace Network;
