#pragma once

#include <QtCore/QObject>
#include <ccl/ccl_global.h>

namespace Network
{
    class RemoteData : public QObject
    {
        Q_OBJECT
        PROPERTY_DEF(float, storageSpace, setStorageSpace, m_storageSpace)

        public:
            explicit RemoteData(QObject* parent = nullptr);

            signals:
                void storageSpaceChanged();

        private:
            float m_storageSpace = 0;
    };
} // namespace Network;
