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

            signals:

        private:
            explicit ImageProcessing(QObject *parent = nullptr);
            Map::ImageModel* m_model;
    };
} // namespace Processing;
