#ifndef MEDIUM_LOG_HPP
#define MEDIUM_LOG_HPP

#include "../Log.hpp"

class MediumLog : public Log {
   public:
    MediumLog(
        TextureHolder& textureHolder, int seasonIndex, Directions::ID direction
    );

    int getLength() const override;

   private:
    Textures::ID getTextureID() const final;
};

#endif
