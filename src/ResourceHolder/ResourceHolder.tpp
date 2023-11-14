#include <exception>

#include "ResourceHolder.hpp"

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(
    Identifier id, const std::string& filename
) {
    std::unique_ptr<Resource> resource(new Resource());

    if (!resource->loadFromFile(filename)) {
        throw std::runtime_error("Failed to load " + filename);
    }

    mResourceMap[id] = std::move(resource);
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) {
    auto found = mResourceMap.find(id);

    if (found == mResourceMap.end()) {
        throw std::runtime_error("Failed to get resource");
    }

    return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const {
    auto found = mResourceMap.find(id);

    if (found == mResourceMap.end()) {
        throw std::runtime_error("Failed to get resource");
    }

    return *found->second;
}
