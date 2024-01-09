#ifndef SHORT_LOG_HPP
#define SHORT_LOG_HPP

#include "../Log.hpp"

class ShortLog : public Log {
   public:
    ShortLog(
        TextureHolder& textureHolder, int seasonIndex, Directions::ID direction
    );

    int getLength() const override;

   private:
    Textures::ID getTextureID() const final;
};

#endif
