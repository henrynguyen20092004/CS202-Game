#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "../ResourceHolder/ResourceHolder.hpp"

class Animation {
   public:
    Animation(
        sf::Sprite& sprite, sf::Vector2i frameSize, std::size_t numFrames,
        sf::Time duration, bool repeat
    );

    void update(sf::Time deltaTime);

   private:
    sf::Sprite& mSprite;
    sf::Vector2i mFrameSize;
    std::size_t mNumFrames;
    std::size_t mCurrentFrame;
    sf::Time mDuration;
    sf::Time mElapsedTime;
    bool mRepeat;
};

#endif
