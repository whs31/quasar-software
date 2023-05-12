#pragma once

#include <Definitions>
#include <QtCore/QObject>

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

        constexpr __global float INITIAL_OPACITY = 1;
        constexpr __global bool INITIAL_VISIBILITY = true;

        public:
            Map::ImageModel* model();
            bool exists(const QString& name);

            public slots:
                void processImage(const QString& filename);

            signals:
                __property_signal busyChanged();

        private:
            explicit ImageProcessing(QObject* parent = nullptr);
            Map::ImageModel* m_model;

            void __async asyncProcess(const QString& filename);
            QByteArray fileToByteArray(const QString& path);

        private:
            bool m_busy;
    };
} // namespace Processing;
