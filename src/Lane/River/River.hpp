#ifndef RIVER_HPP
#define RIVER_HPP

#include "../Lane.hpp"

class River : public Lane {
   public:
    River(TextureHolder& textureHolder, const sf::Vector2f& position);

   private:
    void buildScene();
};

#endif
