#include "Terminal.h"

#define handle_error(msg) perror(msg)

Terminal::Terminal()
{
    plugin_name = "Terminal";
    plugin_window = this;
}

Terminal::~Terminal()
{
    qDebug() << "Destructor Terminal";

    //this->setUpdatesEnabled(false);
    //qDeleteAll(this->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));
    //this->setUpdatesEnabled(true);
}

void Terminal::Init(QWidget* _parent, QHash<QString, QVariant>* _config, PluginHostAPI* _HostAPI){
	this->setParent(_parent);
	this->setWindowTitle(plugin_name);
	this->SetPluginHostAPI(_HostAPI);
	this->SetConfig(_config);
	
	PluginAPI->addMethod((void*)this, "print");
    
    
    label = new QLabel();
    
    this->QDockWidget::setWidget(label);
    label->setText("LOADED");
    label->show();

    qDebug() << "int1" << fromConfig("int1");
    qDebug() << "int2" << fromConfig("int2");
}

QVariant Terminal::print(QVariant cmd){
    
    qDebug() << "This:" << this;
    qDebug() << "Call print";
    qDebug() << "arg = " << cmd;
    label->setText(cmd.toString());
    
    return 0;
}
