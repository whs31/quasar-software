#include <pluginHostAPI.h>
#include <QMetaMethod>
#include <QMetaObject>
#include <QSettings>
#include <QVariant>

PluginHostAPI::PluginHostAPI()
{

}


int PluginHostAPI::parseConfig(QObject* prop, QString path ){
    if(!prop){
        return -1;
    }
    
    QSettings s(path, QSettings::IniFormat);
    
    if(!s.isWritable()){
        return -2;
    }
    
    if( !s.value("main/plugin_list").isValid() ){
        s.setValue("main/plugin_list", "");
    }
    
    QStringList keys = s.allKeys();
    foreach (QString key, keys){
        prop->setProperty(key.toUtf8().data(), s.value(key) );
    }
    
    return 0;
}

void PluginHostAPI::addData(QString name, void* data, int size)
{
    PluginData *sData = (struct PluginData *)malloc(sizeof(struct PluginData) );
    
    sData->data = data;
    sData->size = size;
    
    dataMap.insert(name, sData);
}


PluginData *PluginHostAPI::getData(QString name)
{
    PluginData *sData = (struct PluginData *)dataMap[name];
    return sData;
}


void PluginHostAPI::removeData(QString name)
{
    PluginData *sData = (struct PluginData *)dataMap[name];
    free(sData);
    dataMap.remove(name);
}


QVariant PluginHostAPI::execute(QString class_name, QString method, QVariant arg)
{
    QVariant val;
    
    QString cmd = QString("%1.%2").arg(class_name, method);
    const char* cmd_str = cmd.toStdString().c_str();
    PluginData *sData = (struct PluginData *)dataMap[cmd_str];
    
    if(!sData){
        return 0;
    }
    
    QObject *w = (QObject*)sData->data;
    
    QMetaObject::invokeMethod( w, method.toStdString().c_str(), 
        Qt::DirectConnection,
        Q_RETURN_ARG(QVariant, val), 
        Q_ARG( QVariant, arg ));
    
    return val;

}

void PluginHostAPI::addMethod(void *class_ptr, QString method){
    
    QObject *w = (QObject*)class_ptr;
    const char* class_name = w->metaObject()->className();
    
    QString tmp = QString("%1.%2").arg(class_name, method);
    
    qDebug() << "addMethod:" << tmp;
    
    addData(tmp, class_ptr, 1);
    
    
}
