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

        public:
            Map::ImageModel* model() const;

            public slots:
                void __slot processImage(const QString& filename);

            signals:

        private:
            explicit ImageProcessing(QObject *parent = nullptr);
            Map::ImageModel* m_model;

            void __async asyncProcess(const QString& filename);

            QByteArray fileToByteArray(const QString& path);
    };
} // namespace Processing;
