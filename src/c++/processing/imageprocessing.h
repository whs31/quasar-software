#pragma once

#include <QtCore/QObject>
#include <vector>

using std::vector;

class QImage;

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
        Q_PROPERTY(float progress READ progress WRITE setProgress NOTIFY progressChanged)

        constexpr static const float INITIAL_OPACITY = 1;
        constexpr static const bool INITIAL_VISIBILITY = true;

        constexpr static const bool DEBUG_SAVE_STRIP_DATA_DESERIALIZED = true;
        constexpr static const bool DEBUG_SHOW_STRIP_DATA_MATRIX = true;
        constexpr static const bool DEBUG_PRESERVE_BINARY = false;

        constexpr static const int CONCURRENT_THREADS_COUNT_TELESCOPIC = 2;
        constexpr static const int CONCURRENT_THREADS_COUNT_STRIP = 4;

        constexpr static const int MAX_PACKAGE_SIZE = 1024;

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
                void processList(const QList<QString>& list);
                void passImage(const Map::Image& image);

            signals:
                void processImageFinished(const Map::Image& image);
                void stripVector8bit(vector<uint8_t> vec, int rows, int columns);
                void concurrencyFinished();

                void progressChanged();

            private:
            explicit ImageProcessing(QObject* parent = nullptr);
            ImageProcessing(const ImageProcessing &);
            ImageProcessing &operator=(const ImageProcessing &);

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
