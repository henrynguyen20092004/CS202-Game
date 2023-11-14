#ifndef RESOURCE_HOLDER_HPP
#define RESOURCE_HOLDER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>

#include "../Identifier/Identifier.hpp"

template <typename Resource, typename Identifier>
class ResourceHolder {
   public:
    void load(Identifier id, const std::string& filename);

    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;

   private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include "ResourceHolder.tpp"

#endif  // RESOURCE_HOLDER_HPP
