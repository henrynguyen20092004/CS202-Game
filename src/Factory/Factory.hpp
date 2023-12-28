#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "../Player/Player.hpp"

class Factory : public SceneNode {
   public:
    typedef std::unique_ptr<Factory> Ptr;

    virtual void handlePlayerCollision(Player& player) = 0;

   protected:
    TextureHolder& mTextureHolder;

    Factory(TextureHolder& textureHolder);

   private:
    virtual void init();
};

#endif
