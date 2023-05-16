#pragma once

#include <QtCore/QObject>
#include <ccl/ccl_global.h>

namespace Processing
{
    class StripProcessing : public QObject
    {
        Q_OBJECT
        DEFINE_AS_SINGLETON(StripProcessing)

        public:
            explicit StripProcessing(QObject* parent = nullptr);

            public slots:
                void processImage(const QString& filename);

            signals:

    };
} // namespace Processing;
