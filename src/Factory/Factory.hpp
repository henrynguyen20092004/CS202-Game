#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "../ResourceHolder/ResourceHolder.hpp"
#include "../SceneNode/SceneNode.hpp"

class Factory : public SceneNode {
   public:
    typedef std::unique_ptr<Factory> Ptr;

    Factory(TextureHolder& textureHolder);

   protected:
    TextureHolder& mTextureHolder;
};

#endif
