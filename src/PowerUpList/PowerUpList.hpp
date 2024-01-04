#ifndef POWER_UP_LIST_HPP
#define POWER_UP_LIST_HPP

#include "../PowerUpSettings/PowerUpSettings.hpp"

class PowerUpList : public SceneNode {
   public:
    typedef std::unique_ptr<PowerUpList> Ptr;

    PowerUpList(
        PowerUpSettings& powerUpSettings, TextureHolder& textureHolder,
        FontHolder& fontHolder, sf::View& worldView, Player& player
    );

    void addPowerUp(PowerUp::Type type);

   private:
    PowerUpSettings& mPowerUpSettings;
    std::map<PowerUp::Type, PowerUp*> mPowerUps;

    void handleEventCurrent(const sf::Event& event) override;
    void initPowerUps(
        TextureHolder& textureHolder, FontHolder& fontHolder,
        sf::View& worldView, Player& player
    );
};

#endif
