#pragma once

#include <Definitions>
#include <QtCore/QObject>

namespace OS
{
    class Filesystem : public QObject
    {
        Q_OBJECT
        DEFINE_AS_SINGLETON(Filesystem)

        public:
            __exposed bool fetchImageDirectory();

            signals:
                __signal imageCached(const QString& filename);

        private:
            Filesystem(QObject* parent = nullptr);
            bool checkOcurrence(QString target_folder, QString filename);
    };
} // namespace OS;
