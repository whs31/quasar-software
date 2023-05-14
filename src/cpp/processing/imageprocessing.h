#pragma once

#include <QtCore/QObject>
#include <ccl/ccl_global.h>

namespace Map {
    class ImageModel;
}

namespace Processing
{
    class ImageProcessing : public QObject
    {
        Q_OBJECT
        DEFINE_AS_SINGLETON(ImageProcessing)

        PROPERTY_DEF(bool, busy, setBusy, m_busy);

        constexpr static float INITIAL_OPACITY = 1;
        constexpr static bool INITIAL_VISIBILITY = true;

        public:
            Map::ImageModel* model();
            bool exists(const QString& name);

            public slots:
                void processImage(const QString& filename);

            signals:
                void busyChanged();

        private:
            explicit ImageProcessing(QObject* parent = nullptr);
            Map::ImageModel* m_model;

            void asyncProcess(const QString& filename);
            QByteArray fileToByteArray(const QString& path);

        private:
            bool m_busy;
    };
} // namespace Processing;
