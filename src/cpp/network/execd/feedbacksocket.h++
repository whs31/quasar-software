#pragma once

#include "../abstractudpsocket.h++"

class FeedbackSocket : public Network::AbstractUDPSocket
{
    Q_OBJECT
public:
    explicit FeedbackSocket(QObject *parent = nullptr);
};
