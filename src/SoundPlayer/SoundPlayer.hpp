#ifndef SOUND_PLAYER_HPP
#define SOUND_PLAYER_HPP

#include <list>

#include "../Identifier/Identifier.hpp"
#include "../ResourceHolder/ResourceHolder.hpp"

class SoundPlayer : private sf::NonCopyable {
   public:
    SoundPlayer(SoundHolder& soundHolder);

    void play(Sounds::ID soundID);
    void play(Sounds::ID soundID, sf::Vector2f position);

    void removeStoppedSounds();
    void setListenerPosition(sf::Vector2f position);
    sf::Vector2f getListenerPosition() const;

   private:
    SoundHolder& mSoundHolder;
    std::list<sf::Sound> mSounds;
};

#endif
