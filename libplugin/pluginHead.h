#ifndef PLUGIN_HEAD_H
#define PLUGIN_HEAD_H

#include <plugin.h>
#include <QPluginLoader>
#include <QMetaType>

class PluginHostAPI;

class PluginHead : public PluginInterface
{
public:
    PluginHead();
    ~PluginHead();
    void Show() override;
    QString GetName() override;
    virtual QWidget* GetWidget() override;
    virtual void SetParent(QWidget* _parent) override;
    virtual void SetPluginHostAPI(PluginHostAPI* _HostAPI) override;
    virtual void SetConfig(QObject* _config) override;

    QVariant fromConfig(QString key);
    QObject* GetConfig();
    QWidget* GetParent();
    PluginHostAPI* GetHostAPI();
protected:
    QWidget* plugin_window = nullptr;
    QWidget* PluginParent = nullptr;
    PluginHostAPI* PluginAPI = nullptr;
    QObject *config = nullptr;
};

#endif
