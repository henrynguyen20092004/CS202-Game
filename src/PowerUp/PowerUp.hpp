#ifndef POWER_UP_HPP
#define POWER_UP_HPP

#include "../Player/Player.hpp"
#include "../PowerUpIcon/PowerUpIcon.hpp"

class PowerUp : public SceneNode {
   public:
    enum Type {
        Immortality,
        SlowTime,
        TypeButtonCount,
        Regenerate,
        None,
    };

    typedef std::unique_ptr<PowerUp> Ptr;

    PowerUp(
        const PowerUpIconArgs& powerUpIconArgs, Textures::ID textureID,
        Player& player, sf::Time duration
    );

    void start();

    void updateCurrent(sf::Time deltaTime) override;

    void increaseCount();

   protected:
    Player& mPlayer;

   private:
    sf::Time mDuration, mRemainingDuration;
    int mCount = 1;  // TODO: revert after testing
    bool mIsActivated = false;

    virtual void activate() = 0;
    virtual void deactivate();
};

#endif
