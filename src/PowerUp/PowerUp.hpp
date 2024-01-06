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
        None,
    };

    typedef std::unique_ptr<PowerUp> Ptr;

    PowerUp(
        const PowerUpIconArgs& powerUpIconArgs, Textures::ID textureID,
        Player& player, sf::Time duration
    );

    void start();
    void increaseCount();

   protected:
    Player& mPlayer;

   private:
    sf::Time mDuration, mRemainingDuration;
    int mCount = 0;
    bool mIsActivated = false;

    virtual void activate() = 0;
    virtual void deactivate();

    void updateCurrent(sf::Time deltaTime) override;

    void saveCurrent(std::ofstream& fout) const final;
    void loadCurrent(std::ifstream& fin) final;
};

#endif
