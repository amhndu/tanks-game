#ifndef MSGCOMPONENTS_H
#define MSGCOMPONENTS_H
#include "Message.h"
#include <list>
class Receiver
{
public:
    virtual ~Receiver(){};
    virtual void receiveMessage(const Message &msg) {};
};

class MsgGroup
{
public:
    MsgGroup();
    MsgGroup(MsgGroup &&cpy);
    void sendMessage(const Message &msg);
    void clear(){ subscribers.clear(); }
    void subscribe(Receiver *r);
    void unsubscribe(Receiver *r);
private:
    std::list<Receiver*> subscribers;
};
#endif // MSGCOMPONENTS_H
