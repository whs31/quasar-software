#pragma once

#include <QtCore/QObject>
#include <QtCore/QList>
#include <ccl/ccl_global.h>

namespace OS
{
    class Filesystem : public QObject
    {
        Q_OBJECT
        DEFINE_AS_SINGLETON(Filesystem)

        public:
            Q_INVOKABLE bool fetchImageDirectory();

            signals:
                void imageListCached(const QList<QString>& filenames);
                void imageCached(const QString& filename);
                void binaryCached(const QString& filename);

        private:
            Filesystem(QObject* parent = nullptr);
            bool checkOcurrence(QString target_folder, QString filename);

            QList<QString> fetchBinaryList();
    };
} // namespace OS;
