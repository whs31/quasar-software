#pragma once

#include <QtCore/QObject>
#include <QtCore/QList>

//! @namespace Namespace for working with OS-specific
//!            data and filesystems.
namespace OS
{
    //! @class Class, providing access to filesystem
    //!        operations and cache manipulation.
    class Filesystem : public QObject
    {
        Q_OBJECT

        public:
            //! @brief Returns singleton instance of class.
            static Filesystem* get();

            //! @brief   Searches for image files in application
            //!          cache directory.
            //! @details Ignores occurences, already present in model.
            //!          Can be invoked from QML.
            //! @sa      Emits imageListCached() - signal, which holds
            //!          list of filenames, marked for processing.
            Q_INVOKABLE bool fetchImageDirectory();

            //! @brief   Searches for image files in application
            //!          TCP-IO cache directory.
            //! @details Ignores occurences, already present in model.
            //!          Can be invoked from QML.
            //! @sa      Emits imageListCached() - signal, which holds
            //!          list of filenames, marked for processing.
            //! @note    (WIP) Replaces occurence, found in model.
            Q_INVOKABLE void fetchTCPCache();

            public slots:
                //! @brief Exports given list of filenames in LOD0 cache
                //!        to specified folder.
                //! @param ls - list of filenames to export.
                //! @param folder - destination folder.
                void exportImagesToFolder(const QList<QString>& ls, const QString& folder);

            signals:
                void imageListCached(const QList<QString>& filenames);
                void binaryCached(const QString& filename);

        private:
            Filesystem(QObject* parent = nullptr);
            Filesystem(const Filesystem &);
            Filesystem &operator=(const Filesystem &);

            bool checkOcurrence(QString target_folder, QString filename);

            QList<QString> fetchBinaryList();
    };
} // namespace OS;
