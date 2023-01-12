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
    
    initTerminal();
    initSocket();
    
}


void Terminal::initTerminal(){
    
    QVariant tmp;
    int font_size;
    
    tmp = fromConfig("font_size");
    
    if(tmp.isValid()){
        font_size = tmp.toInt();
    }else{
        qDebug() << "Terminal font_size in undefined";
        font_size = 10;
    }
    
    terminal = new QVTerminal(nullptr, font_size);
    this->setWidget(terminal);
}


void Terminal::initSocket(){
    
    QVariant tmp;
    QString address;
    int port;
    
    tmp = fromConfig("address");
    if(!tmp.isValid()){
        qDebug() << "Terminal not found address";
        return;
    }
    address = tmp.toString();
    
    tmp = fromConfig("port");
    if(!tmp.isValid()){
        qDebug() << "Terminal not found port";
        return;
    }
    port = tmp.toInt();
    
    socket = new QUdpSocket(this);
    if(socket->bind(QHostAddress(address), port)){
        qDebug() << "Terminal binded to" << address << port;
    }else{
        qDebug() << "Terminal binding error!!!";
        return;
    }
    
    connect(socket, SIGNAL(readyRead()), this, SLOT(socketRead()));
}


void Terminal::socketRead(){
    
    QByteArray datagram;
    QHostAddress *address = new QHostAddress();
    
    datagram.resize(socket->pendingDatagramSize());
    socket->readDatagram(datagram.data(), datagram.size(), address);

    terminal->appendData(datagram);
}


QVariant Terminal::print(QVariant cmd){
    
    terminal->appendData(cmd.toByteArray());
    return 0;
}