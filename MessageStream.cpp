#include "MessageStream.h"

MessageStream::MessageStream()
{
    //ctor
}

void MessageStream::addGroup(std::string name,MsgGroup &grp)
{
    groups.insert(std::make_pair(name,std::move(grp)));
}
void MessageStream::removeGroup(std::string name)
{
    groups.erase(name);
}
MsgGroup& MessageStream::getGroup(std::string name) //if group 'name' doesn't exist it is created and returned
{
    return groups[name];
}
void MessageStream::sendMessage(const Message &msg,std::string grp)
{
    auto it = groups.find(grp);
    if(it != groups.end())
        it->second.sendMessage(msg);
}
