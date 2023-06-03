#pragma once

#include <QtCore/QObject>
#include <vector>
#include <LPVL/Global>

using std::vector;

namespace Map {
    class Image;
    class StripImage;
    class ImageModel;
}

namespace Processing
{
    class ImageProcessing : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(bool processingImage READ processingImage WRITE setProcessingImage NOTIFY processingImageChanged)
        Q_PROPERTY(bool processingStrip READ processingStrip WRITE setProcessingStrip NOTIFY processingStripChanged)
        LPVL_DECLARE_SINGLETON(ImageProcessing)

        constexpr static float INITIAL_OPACITY = 1;
        constexpr static bool INITIAL_VISIBILITY = true;
        constexpr static bool DEBUG_SAVE_STRIP_DATA_DESERIALIZED = true;

        public:
            enum ImageType {
                Telescopic,
                Strip
            };

            Map::ImageModel* model();

            bool exists(const QString& name);

            bool processingImage() const; void setProcessingImage(bool);
            bool processingStrip() const; void setProcessingStrip(bool);

            public slots:
                void processList(const QList<QString>& list);
                void passImage(const Map::Image& image);

            signals:
                void processImageFinished(const Map::Image& image);
                void stripVector8bit(vector<uint8_t> vec, int rows, int columns);
                void processingImageChanged();
                void processingStripChanged();

        private:
            explicit ImageProcessing(QObject* parent = nullptr);
            Map::ImageModel* m_model;

            void asyncProcess(const QString& filename);
            void asyncStripProcess(const QString& filename);
            QByteArray fileToByteArray(const QString& path);

        private:
            bool m_processingImage = false;
            bool m_processingStrip = false;
    };
} // namespace Processing;
