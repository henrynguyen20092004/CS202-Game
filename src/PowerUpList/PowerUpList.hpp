#ifndef POWER_UP_LIST_HPP
#define POWER_UP_LIST_HPP

#include "../PowerUpSettings/PowerUpSettings.hpp"

class PowerUpList : public SceneNode {
   public:
    typedef std::unique_ptr<PowerUpList> Ptr;

    PowerUpList(Player& player, PowerUpSettings& powerUpSettings);

    void addPowerUp(PowerUp::Type type);

   private:
    PowerUpSettings& mPowerUpSettings;
    std::map<PowerUp::Type, std::unique_ptr<PowerUp>> mPowerUps;

    void handleEventCurrent(const sf::Event& event) override;
    void updateCurrent(sf::Time deltaTime) override;

    void initPowerUps(Player& player);
};

#endif
