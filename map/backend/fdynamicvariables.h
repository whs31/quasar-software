#ifndef FDYNAMICVARIABLES_H
#define FDYNAMICVARIABLES_H

#include "qqml.h"
#include <QObject>

class FDynamicVariables : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool followPlane READ followPlane WRITE setFollowPlane NOTIFY followPlaneChanged);
    Q_PROPERTY(bool enableTooltip READ enableTooltip WRITE setEnableTooltip NOTIFY enableTooltipChanged);
    Q_PROPERTY(bool enableRoute READ enableRoute WRITE setEnableRoute NOTIFY enableRouteChanged);
    Q_PROPERTY(bool enablePredict READ enablePredict WRITE setEnablePredict NOTIFY enablePredictChanged);
    Q_PROPERTY(bool enablePredictDiagram READ enablePredictDiagram WRITE setEnablePredictDiagram NOTIFY enablePredictDiagramChanged);
    QML_ELEMENT

public:
    explicit FDynamicVariables(QObject *parent = nullptr);

    bool followPlane();
    bool enableTooltip();
    bool enableRoute();
    bool enablePredict();
    bool enablePredictDiagram();

    void setFollowPlane(bool value);
    void setEnableTooltip(bool value);
    void setEnableRoute(bool value);
    void setEnablePredict(bool value);
    void setEnablePredictDiagram(bool value);

signals:
    void followPlaneChanged(bool b);
    void enableTooltipChanged();
    void enableRouteChanged();
    void enablePredictChanged();
    void enablePredictDiagramChanged();

private:
    bool _followPlane;
    bool _enableTooltip;
    bool _enableRoute;
    bool _enablePredict;
    bool _enablePredictDiagram;


};

#endif // FDYNAMICVARIABLES_H
