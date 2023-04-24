
#ifndef FEEDBACKSOCKET_H
#define FEEDBACKSOCKET_H

#include <abstractudpsocket.h++>



class FeedbackSocket : public AbstractUDPSocket
{
    Q_OBJECT
public:
    explicit FeedbackSocket(QObject *parent = nullptr);
};

#endif // FEEDBACKSOCKET_H
