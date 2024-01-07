#ifndef HALO_HPP
#define HALO_HPP

#include "../SpriteNode/SpriteNode.hpp"

class Halo : public SpriteNode {
   public:
    typedef std::unique_ptr<Halo> Ptr;

    Halo(TextureHolder& textureHolder, Textures::ID textureID);

    void show();
    void hide();

   private:
    sf::IntRect mTextureRect;
};

#endif
