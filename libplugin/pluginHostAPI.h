#ifndef PluginHostAPI_H
#define PluginHostAPI_H

#include <plugin.h>

typedef struct PluginData
{
    const void* data;
    PluginDataTypes::Type type;
    int size;
};

class PluginHostAPI
{
public:
    PluginHostAPI();
    void addData(QString name, void* data, int size);
    PluginData *getData(QString name);
    void removeData(QString name);
    QVariant execute(QString class_name, QString method, QVariant arg);
    
    void addMethod(void *class_ptr, QString method);
    
    int parseConfig(QObject* prop, QString path = QString("plugin_config.ini") );

private:
    QMap<QString, void*> dataMap;
};

#endif // PluginHostAPI_H
