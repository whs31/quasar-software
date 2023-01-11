#ifndef Terminal_H
#define Terminal_H

#include <QtCore/qglobal.h>
#include <QHBoxLayout>
#include <QLabel>
#include <QStyle>
#include <csignal>

#include <plugin.h>
#include <QDockWidget>


#if defined(Terminal_LIBRARY)
#  define Terminal_EXPORT Q_DECL_EXPORT
#else
#  define Terminal_EXPORT Q_DECL_IMPORT
#endif




class Terminal : public QDockWidget, PluginHead
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "PluginInterface")
    Q_INTERFACES(PluginInterface)

public:
    explicit Terminal();
    ~Terminal();
    
    void Init(QWidget* _parent, QHash<QString, QVariant>* _config, PluginHostAPI* _HostAPI);
    
public slots:
    QVariant print(QVariant cmd);

private:
    QLabel* label;

};

#endif
