#ifndef POWER_UP_SETTINGS_HPP
#define POWER_UP_SETTINGS_HPP

#include "../PowerUp/PowerUp.hpp"

class PowerUpSettings {
   public:
    PowerUpSettings();

    void assignKey(sf::Keyboard::Key key, PowerUp::Type type);
    PowerUp::Type getPowerUpType(sf::Keyboard::Key key) const;

   private:
    std::map<sf::Keyboard::Key, PowerUp::Type> mKeyBinding;
};

#endif
