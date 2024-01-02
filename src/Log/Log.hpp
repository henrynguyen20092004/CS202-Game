#ifndef LOG_HPP
#define LOG_HPP

#include "../MovableSpriteNode/MovableSpriteNode.hpp"

class Log : public MovableSpriteNode {
   public:
    typedef std::unique_ptr<Log> Ptr;

    Directions::ID getDirection() const;
    virtual int getLength() const = 0;

    void setDirection(Directions::ID direction);

   protected:
    Log(TextureHolder& textureHolder, Textures::ID textureID,
        sf::IntRect textureRect, Directions::ID direction);

   private:
    Directions::ID mDirection;

    virtual void updateCurrent(sf::Time deltaTime) override;
};

#endif
