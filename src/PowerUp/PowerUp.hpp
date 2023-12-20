#ifndef POWER_UP_HPP
#define POWER_UP_HPP

#include "../Player/Player.hpp"

class PowerUp {
   public:
    enum class Type {
        None,
        BonusHealth,
        Immortality,
        IncreaseScore,
        SlowTime,
    };

    PowerUp(sf::Time duration, Player& player);

    void start();

    void update(sf::Time deltaTime);

    void increaseCount();

   protected:
    Player& mPlayer;

   private:
    sf::Time mDuration, mRemainingDuration;

    int mCount = 0;
    bool mIsActivated = false;

    virtual void activate() = 0;
    virtual void deactivate();
};

#endif
