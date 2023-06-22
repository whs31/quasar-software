#pragma once

#include <QtCore/QObject>
#include <vector>
#include "map/entities/image.h"
#include "map/entities/stripimage.h"

using std::vector;

namespace Map
{
    class ImageModel;
} // Map

class QImage;

namespace Processing
{
    class ImageProcessing : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(float progress READ progress WRITE setProgress NOTIFY progressChanged)

        public:
            enum ImageType
            {
                Telescopic,
                Strip
            };

            static ImageProcessing* get();

            Map::ImageModel* model();

            bool exists(const QString& name);
            int indexFrom(const QString& name) noexcept;

            [[nodiscard]] float progress() const; void setProgress(float);

            public slots:
                void processList(QList<QString> list);
                void passImage(Map::Image image);

            signals:
                void processImageFinished(Map::Image image);
                void processStripFinished(Map::StripImage image);
                void stripVector8bit(vector<uint8_t> vec, int rows, int columns);
                void concurrencyFinished();

                void progressChanged();

        private:
            explicit ImageProcessing(QObject* parent = nullptr);
            ImageProcessing(const ImageProcessing&);
            ImageProcessing& operator=(const ImageProcessing&);

            void asyncProcess(const QString& filename);
            void asyncStripProcess(const QString& filename);
            QByteArray fileToByteArray(const QString& path);
            Map::Image decodeTelescopic(const QString& path);
            QImage cutImage(const Map::Image& image) noexcept;

        private:
            Map::ImageModel* m_model;
            float m_progress;
            int m_total;
            int m_processed;
    };
} // namespace Processing;
