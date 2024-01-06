#ifndef ROCK_HPP
#define ROCK_HPP

#include "../Obstacle.hpp"

class Rock : public Obstacle {
   public:
    Rock(TextureHolder& textureHolder);

   private:
    Textures::ID getTextureID() const final;
};

#endif
