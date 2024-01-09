#include "SoundPlayer.hpp"

#include <SFML/Audio/Listener.hpp>
#include <cmath>

namespace {
const float ListenerZ = 300.f;
const float Attenuation = 8.f;
const float MinDistance2D = 200.f;
const float MinDistance3D =
    std::sqrt(MinDistance2D * MinDistance2D + ListenerZ * ListenerZ);
}  // namespace

SoundPlayer::SoundPlayer(SoundHolder& soundHolder) : mSoundHolder(soundHolder) {
    sf::Listener::setDirection(0.f, 0.f, -1.f);
}

void SoundPlayer::play(Sounds::ID soundID) {
    play(soundID, getListenerPosition());
}

void SoundPlayer::play(Sounds::ID soundID, sf::Vector2f position) {
    mSounds.push_back(sf::Sound());
    sf::Sound& sound = mSounds.back();

    sound.setBuffer(mSoundHolder.get(soundID));
    sound.setPosition(position.x, -position.y, 0.f);
    sound.setAttenuation(Attenuation);
    sound.setMinDistance(MinDistance3D);

    sound.play();
}

void SoundPlayer::removeStoppedSounds() {
    mSounds.remove_if([](const sf::Sound& s) {
        return s.getStatus() == sf::Sound::Stopped;
    });
}

void SoundPlayer::setListenerPosition(sf::Vector2f position) {
    sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}

sf::Vector2f SoundPlayer::getListenerPosition() const {
    sf::Vector3f position = sf::Listener::getPosition();
    return sf::Vector2f(position.x, -position.y);
}