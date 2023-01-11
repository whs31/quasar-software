#include "pluginHead.h"

PluginHead::PluginHead()
{
}

PluginHead::~PluginHead()
{
    qDebug() << "~PluginHead" << plugin_name;
}

void PluginHead::Show()
{
}

QString PluginHead::GetName()
{
    return plugin_name;
}

QWidget* PluginHead::GetWidget()
{
    return plugin_window;
}

void PluginHead::SetParent(QWidget* _parent)
{
    PluginParent = _parent;
}

void PluginHead::SetPluginHostAPI(PluginHostAPI* _HostAPI)
{
    PluginAPI = _HostAPI;
}

void PluginHead::SetConfig(QHash<QString, QVariant>* _config){
    config = _config;
}

QVariant PluginHead::fromConfig(QString key){
    if(!config){
        return QVariant::Invalid;
    }
    key.prepend("/");
    key.prepend(plugin_name);
    return config->value(key);
}

