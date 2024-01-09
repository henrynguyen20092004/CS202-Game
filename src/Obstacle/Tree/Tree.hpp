#ifndef TREE_HPP
#define TREE_HPP

#include "../Obstacle.hpp"

class Tree : public Obstacle {
   public:
    Tree(TextureHolder& textureHolder, int seasonIndex);

   private:
    Textures::ID getTextureID() const final;
};

#endif
