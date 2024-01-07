#include "SoundNode.hpp"

#include "../SoundPlayer/SoundPlayer.hpp"

SoundNode::SoundNode(SoundPlayer& player) : mSoundPlayer(player) {}

void SoundNode::playSound(Sounds::ID soundID, sf::Vector2f position) {
    mSoundPlayer.play(soundID, position);
}
