#pragma once

#include <Definitions>
#include <QtCore/QList>
#include <QtQuick/QQuickPaintedItem>
#include <vector>

class QTimer;
class MultiGraph : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int axisCount READ axisCount WRITE setAxisCount NOTIFY axisCountChanged)
    Q_PROPERTY(float timeLength READ timeLength WRITE setTimeLength NOTIFY timeLengthChanged)
    Q_PROPERTY(float valueMaxSize READ valueMaxSize WRITE setValueMaxSize NOTIFY valueMaxSizeChanged)
    Q_PROPERTY(QList<QString> axisNames READ axisNames WRITE setAxisNames NOTIFY axisNamesChanged)
    Q_PROPERTY(QList<QString> axisColors READ axisColors WRITE setAxisColors NOTIFY axisColorsChanged)
    Q_PROPERTY(QString backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QString foregroundColor READ foregroundColor WRITE setForegroundColor NOTIFY foregroundColorChanged)
    Q_PROPERTY(float timeInterval READ timeInterval WRITE setTimeInterval NOTIFY timeIntervalChanged)

    public:
        MultiGraph(QQuickItem* parent = nullptr);
        void paint(QPainter* painter) override;

        __qml void setValues(const QList<float>& values);

        __getter float timeLength() const;
        __setter void setTimeLength(float other);

        __getter float valueMaxSize() const;
        __setter void setValueMaxSize(float other);

        __getter QList<QString> axisNames() const;
        __setter void setAxisNames(const QList<QString> &other);

        __getter QList<QString> axisColors() const;
        __setter void setAxisColors(const QList<QString> &other);

        __getter float timeInterval() const;
        __setter void setTimeInterval(float other);

        __getter int axisCount() const;
        __setter void setAxisCount(int newAxisCount);

        __getter QString backgroundColor() const;
        __setter void setBackgroundColor(const QString &newBackgroundColor);

        __getter QString foregroundColor() const;
        __setter void setForegroundColor(const QString &newForegroundColor);

        signals:
            __signal timeLengthChanged();
            __signal valueMaxSizeChanged();
            __signal axisNamesChanged();
            __signal axisColorsChanged();
            __signal timeIntervalChanged();
            __signal axisCountChanged();
            __signal backgroundColorChanged();
            __signal foregroundColorChanged();

    private:
        QTimer* timer;
        std::vector<std::vector<float>> storage;
        std::vector<float> storage_trigger;

        float m_timeLength = 10; // s
        float m_valueMaxSize = 1024; // 1 kb
        QList<QString> m_axisNames = { "Axis 1", "Axis 2", "Axis 3", "Axis 4", "Axis 5", "Axis 6", "Axis 7", "Axis 8", "Axis 9", "Axis 10"};
        QList<QString> m_axisColors = { "red", "green", "yellow", "orange", "purple", "magenta", "brown", "cyan", "gray", "white"};
        float m_timeInterval = 1; // s
        int m_axisCount = 10;
        QString m_backgroundColor = "black";
        QString m_foregroundColor = "white";
};
