#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "../Identifier/Identifier.hpp"
#include "../ResourceHolder/ResourceHolder.hpp"
#include "../SceneNode/SceneNode.hpp"

class Factory : public SceneNode {
   public:
    typedef std::unique_ptr<Factory> Ptr;

    Factory(TextureHolder& textureHolder);

    virtual void setVelocityPercent(float percent);

    virtual Directions::ID getDirection() const;

   protected:
    TextureHolder& mTextureHolder;
};

#endif
