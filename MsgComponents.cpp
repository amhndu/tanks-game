#include "MsgComponents.h"

MsgGroup::MsgGroup()
{}
MsgGroup::MsgGroup(MsgGroup &&cpy) : subscribers(std::move(cpy.subscribers))
{}

void MsgGroup::sendMessage(const Message &msg)
{
    for(auto &R : subscribers) R->receiveMessage(msg);
}
void MsgGroup::unsubscribe(Receiver *r)
{
    subscribers.remove(r);
}
void MsgGroup::subscribe(Receiver *r)
{
    subscribers.push_back(r);
}
