#ifndef POWER_UP_SETTINGS_HPP
#define POWER_UP_SETTINGS_HPP

#include "../PowerUp/PowerUp.hpp"

class PowerUpSettings {
   public:
    PowerUpSettings(bool isPlayer2 = false);

    void assignKey(sf::Keyboard::Key key, PowerUp::Type type);
    PowerUp::Type getPowerUpType(sf::Keyboard::Key key) const;
    sf::Keyboard::Key getAssignedKey(PowerUp::Type type) const;

    void setToDefault(bool isPlayer2 = false);

   private:
    std::map<sf::Keyboard::Key, PowerUp::Type> mKeyBinding;
};

#endif
