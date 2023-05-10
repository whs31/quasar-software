#pragma once

#include <Definitions>
#include <QtCore/QObject>

namespace OS
{
    class Filesystem : public QObject
    {
        Q_OBJECT
        DECLARE_SINGLETON(Filesystem)

        public:
            __qml bool fetchImageDirectory();

            signals:
                __signal imageCached(const QString& filename);

        private:
            Filesystem(QObject* parent = nullptr);
            bool checkOcurrence(QString target_folder, QString filename);
    };
} // namespace OS;
