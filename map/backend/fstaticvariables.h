#ifndef FSTATICVARIABLES_H
#define FSTATICVARIABLES_H

#include "qqml.h"
#include <QObject>

class FStaticVariables : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float predictRange READ predictRange WRITE setPredictRange NOTIFY predictRangeChanged);
    Q_PROPERTY(bool useBase64 READ useBase64 WRITE setUseBase64 NOTIFY useBase64Changed);
    Q_PROPERTY(bool testMode READ testMode WRITE setTestMode NOTIFY testModeChanged);
    QML_ELEMENT

public:
    explicit FStaticVariables(QObject *parent = nullptr);

    float predictRange();
    bool useBase64();
    bool testMode();

    void setPredictRange(float value);
    void setUseBase64(bool value);
    void setTestMode(bool value);

signals:
    void predictRangeChanged();
    void useBase64Changed();
    void testModeChanged();

private:
    bool _predictRange;
    bool _useBase64;
    bool _testMode;

};

#endif // FSTATICVARIABLES_H
