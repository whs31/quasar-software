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

void PluginHead::SetConfig(QObject* _config){
    config = _config;
}

QObject* PluginHead::GetConfig()
{
    return config;
}


QVariant PluginHead::fromConfig(QString key){
    if(!config){
        return QVariant::Invalid;
    }
    key.prepend("/");
    key.prepend(plugin_name);
    return config->property((const char*)key.toUtf8().data());
}

QWidget* PluginHead::GetParent(){
    return PluginParent;
}

PluginHostAPI* PluginHead::GetHostAPI(){
    return PluginAPI;
}

