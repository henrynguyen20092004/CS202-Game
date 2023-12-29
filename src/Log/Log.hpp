#ifndef LOG_HPP
#define LOG_HPP

#include "../Entity/Entity.hpp"

class Log : public Entity {
   public:
    typedef std::unique_ptr<Log> Ptr;

    Directions::ID getDirection() const;
    void setDirection(Directions::ID direction);

    virtual void handlePlayerCollision(Player& player) override;

   protected:
    Log(TextureHolder& textureHolder, Textures::ID textureID,
        Directions::ID direction);

   private:
    Directions::ID mDirection;

    virtual void updateCurrent(sf::Time deltaTime) override;
};

#endif
