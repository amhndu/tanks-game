#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <memory>
#include <map>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceManager
{
    public:
        ResourceManager() = default;
        bool load(Identifier id, const std::string& file)
        {
            std::unique_ptr<Resource> a(new Resource());
            bool status = a->loadFromFile(file);
            auto x = resMap.insert(std::make_pair(id,std::move(a)));
            assert(x.second);
            return status;
        }
        template<typename Parameter>
        bool load(Identifier id, const std::string& file,Parameter secParam)
        {
            std::unique_ptr<Resource> a(new Resource());
            bool status = a->loadFromFile(file,secParam);
            resMap.insert(std::make_pair(id,std::move(a)));
            return status;
        }
        Resource &get(Identifier id)
        {
            auto res = resMap.find(id);
            assert(res != resMap.end());
            return *(res->second);
        }
    private:
        std::map<Identifier, std::unique_ptr<Resource> > resMap;
};
#include "ResourceIdentifiers.h"
#endif // RESOURCEMANAGER_H
