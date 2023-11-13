#include "TextureHolder.hpp"

#include <exception>

void TextureHolder::load(Textures::ID id, const std::string& filename) {
    std::unique_ptr<sf::Texture> texture(new sf::Texture());
    if (!texture->loadFromFile(filename)) {
        throw std::runtime_error("Failed to load " + filename);
    }

    mTextureMap.insert(std::make_pair(id, std::move(texture)));
}

sf::Texture& TextureHolder::get(Textures::ID id) {
    auto found = mTextureMap.find(id);
    if (found == mTextureMap.end()) {
        throw std::runtime_error("Failed to get texture");
    }

    return *found->second;
}

const sf::Texture& TextureHolder::get(Textures::ID id) const {
    auto found = mTextureMap.find(id);
    if (found == mTextureMap.end()) {
        throw std::runtime_error("Failed to get texture");
    }

    return *found->second;
}