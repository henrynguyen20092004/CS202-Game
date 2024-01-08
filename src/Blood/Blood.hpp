#ifndef BLOOD_HPP
#define BLOOD_HPP

#include "../SpriteNode/SpriteNode.hpp"
class Blood : public SpriteNode {
   public:
    typedef std::unique_ptr<Blood> Ptr;

    Blood(TextureHolder& textureHolder, int& Health);

   private:
    int& mHealth;
    void updateCurrent(sf::Time deltaTime) override;
   
};
#endif
