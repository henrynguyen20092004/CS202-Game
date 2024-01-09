#ifndef TRAIN_HPP
#define TRAIN_HPP

#include "../Vehicle.hpp"

class Train : public Vehicle {
   public:
    Train(
        TextureHolder& textureHolder, int seasonIndex, Directions::ID direction
    );

   private:
    Textures::ID getTextureID() const final;
};

#endif
