#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "../Entity/Entity.hpp"

class Animal : public Entity {
   public:
    typedef std::unique_ptr<Animal> Ptr;

   protected:
    Animal(TextureHolder& textureHolder, Textures::ID textureID);
};

#endif
