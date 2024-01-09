#ifndef LONG_LOG_HPP
#define LONG_LOG_HPP

#include "../Log.hpp"

class LongLog : public Log {
   public:
    LongLog(
        TextureHolder& textureHolder, int seasonIndex, Directions::ID direction
    );

    int getLength() const override;

   private:
    Textures::ID getTextureID() const final;
};

#endif
