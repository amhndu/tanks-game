#ifndef MESSAGESTREAM_H
#define MESSAGESTREAM_H
#include "MsgComponents.h"
#include <map>

class MessageStream
{
    public:
        MessageStream();
        void addGroup(std::string name,MsgGroup &grp);
        void removeGroup(std::string name);
        MsgGroup& getGroup(std::string name);
        void sendMessage(const Message &msg,std::string grp);
    private:
        std::map<std::string,MsgGroup> groups;
};

#endif // MESSAGESTREAM_H
