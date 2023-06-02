#pragma once

#include <QtCore/QObject>
#include <QtCore/QList>
#include <LPVL/Global>

namespace OS
{
    class Filesystem : public QObject
    {
        Q_OBJECT
        LPVL_DECLARE_SINGLETON(Filesystem)

        public:
            Q_INVOKABLE bool fetchImageDirectory();
            Q_INVOKABLE void fetchTCPCache();

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
