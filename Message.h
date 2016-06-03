#ifndef MESSAGE_H
#define MESSAGE_H
#include <memory>
#include <vector>
#include <string>

class MsgItemBase{};

template<typename T>
class MsgItem : public MsgItemBase
{
public:
    MsgItem(const T& val) : item(val) {}
    T item;
};

class Message
{
    public:
        Message();
        Message(const std::string& id) : ID(id) {}
        ~Message() = default;
        template<typename... T>
        Message(const std::string& id,T... items) : ID(id) { add(items...); }

        template<typename T,typename... Tail>
        void add(const T& a,Tail... tail)
        {
            data.push_back(std::unique_ptr<MsgItemBase>(new MsgItem<T>(a)));
            add(tail...);
        }
        void add(){};

        template<typename T>
        const T& getItem(std::size_t n) const
        {
            return static_cast<MsgItem<T>*>(data[n].get())->item;
        }

        std::string ID;
    private:
        std::vector<std::unique_ptr<MsgItemBase>> data;
};

#endif // MESSAGE_H
