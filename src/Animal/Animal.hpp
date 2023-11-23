#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <SFML/Audio.hpp>

#include "../Identifier/Identifier.hpp"
#include "../MovableSpriteNode/MovableSpriteNode.hpp"

class Animal : public MovableSpriteNode {
   public:
    typedef std::unique_ptr<Animal> Ptr;

   protected:
    sf::SoundBuffer mSoundBuffer;
    sf::Sound mSound;
    Animal(const sf::Texture& texture);
    virtual void updateCurrent(float deltaTime) = 0;
    // virtual void powerUp() = 0;

   private:
    virtual void getSound() = 0;
    virtual void setSound(Sound::ID soundBuffer) = 0;
};

#endif
