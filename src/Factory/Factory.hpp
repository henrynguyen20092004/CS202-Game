#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "../Player/Player.hpp"
#include "../ResourceHolder/ResourceHolder.hpp"
#include "../SceneNode/SceneNode.hpp"

class Factory : public SceneNode {
   protected:
    Factory(TextureHolder& textureHolder);

   public:
    typedef std::unique_ptr<Factory> Ptr;

    virtual void handlePlayerCollision(Player& player) = 0;

   protected:
    TextureHolder& mTextureHolder;

   private:
    virtual void init();
};

#endif
