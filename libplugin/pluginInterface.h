#ifndef PLUGIN_INTERFACE_H
#define PLUGIN_INTERFACE_H

#include <plugin.h>

class PluginHostAPI;

class PluginInterface
{
public:
    virtual ~PluginInterface() {}
    virtual void Show() = 0;
    virtual QString GetName() = 0;
    virtual QWidget* GetWidget() = 0;
    virtual void SetParent(QWidget* _parent) = 0;
    virtual void SetPluginHostAPI(PluginHostAPI* _HostAPI) = 0;
    virtual void SetConfig(QHash<QString, QVariant>* _config) = 0;
    virtual void Init(QWidget* _parent, QHash<QString, QVariant>* _config, PluginHostAPI* _HostAPI) = 0;

protected:
    QString plugin_name = "plugin";

private:
};


QT_BEGIN_NAMESPACE

#define PluginInterface_iid "PluginInterface"

Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_iid)
QT_END_NAMESPACE

#endif // PLUGIN_INTERFACE_H
