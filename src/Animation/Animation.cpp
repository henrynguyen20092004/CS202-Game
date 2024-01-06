#include "Animation.hpp"

#include "../FileIO/FileIO.hpp"

Animation::Animation(
    sf::Sprite& sprite, sf::Vector2i frameSize, std::size_t numFrames,
    sf::Time duration, bool repeat
)
    : mSprite(sprite),
      mFrameSize(frameSize),
      mNumFrames(numFrames),
      mCurrentFrame(0),
      mDuration(duration),
      mRepeat(repeat) {}

void Animation::update(sf::Time deltaTime) {
    sf::Time timePerFrame = mDuration / static_cast<float>(mNumFrames);
    sf::Vector2u textureBounds(mSprite.getTexture()->getSize());
    sf::IntRect textureRect = mSprite.getTextureRect();

    if (!mCurrentFrame) {
        textureRect = sf::IntRect(0, 0, mFrameSize.x, mFrameSize.y);
    }

    mElapsedTime += deltaTime;

    while (mElapsedTime >= timePerFrame &&
           (mCurrentFrame <= mNumFrames || mRepeat)) {
        textureRect.left += textureRect.width;

        if (textureRect.left + textureRect.width > textureBounds.x) {
            textureRect.left = 0;
            textureRect.top += textureRect.height;
        }

        mElapsedTime -= timePerFrame;

        if (mRepeat) {
            mCurrentFrame = (mCurrentFrame + 1) % mNumFrames;

            if (!mCurrentFrame) {
                textureRect = sf::IntRect(0, 0, mFrameSize.x, mFrameSize.y);
            }
        } else {
            mCurrentFrame++;
        }
    }

    mSprite.setTextureRect(textureRect);
}

void Animation::save(std::ofstream& fout) const {
    fout << mCurrentFrame << ' ';
    fout << mElapsedTime << '\n';
}

void Animation::load(std::ifstream& fin) {
    fin >> mCurrentFrame;

    float elapsedTime;
    fin >> elapsedTime;
    mElapsedTime = sf::seconds(elapsedTime);
}
