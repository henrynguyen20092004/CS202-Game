#ifndef TEXTURE_HOLDER_HPP
#define TEXTURE_HOLDER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>

#include "../ResourceIdentifiers/ResourceIdentifiers.hpp"

class TextureHolder {
   public:
    void load(Textures::ID id, const std::string& filename);
    sf::Texture& get(Textures::ID id);
    const sf::Texture& get(Textures::ID id) const;

   private:
    std::map<Textures::ID, std::unique_ptr<sf::Texture>> mTextureMap;
};

#endif  // TEXTURE_HOLDER_HPP
