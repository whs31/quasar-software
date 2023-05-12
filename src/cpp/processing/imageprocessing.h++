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
        DECLARE_SINGLETON(ImageProcessing)

        Q_PROPERTY(bool busy READ busy WRITE setBusy NOTIFY busyChanged)

        constexpr __global float INITIAL_OPACITY = 1;
        constexpr __global bool INITIAL_VISIBILITY = true;

        public:
            Map::ImageModel* model();

            __getter bool busy() const;
            __setter void setBusy(bool other);

            bool exists(const QString& name);

            public slots:
                void __slot processImage(const QString& filename);

            signals:
                __signal busyChanged();

        private:
            explicit ImageProcessing(QObject* parent = nullptr);
            Map::ImageModel* m_model;

            void __async asyncProcess(const QString& filename);

            QByteArray fileToByteArray(const QString& path);

        private:
            bool m_busy;
    };
} // namespace Processing;