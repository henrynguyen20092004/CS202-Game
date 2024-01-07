#ifndef BOOK_SOUNDNODE_HPP
#define BOOK_SOUNDNODE_HPP

#include "../Identifier/Identifier.hpp"
#include "../SceneNode/SceneNode.hpp"

class SoundPlayer;

class SoundNode : public SceneNode {
   public:
    explicit SoundNode(SoundPlayer& player);
    void playSound(Sounds::ID soundID, sf::Vector2f position);

   private:
    SoundPlayer& mSoundPlayer;
};

#endif
