#ifndef PLAYER_SETTINGS_HPP
#define PLAYER_SETTINGS_HPP

#include <SFML/Window.hpp>
#include <map>

#include "../Identifier/Identifier.hpp"

class PlayerSettings {
   public:
    PlayerSettings();

    void assignKey(sf::Keyboard::Key key, Directions::ID direction);
    Directions::ID getDirection(sf::Keyboard::Key key) const;
    sf::Keyboard::Key getAssignedKey(Directions::ID direction) const;

   private:
    std::map<sf::Keyboard::Key, Directions::ID> mKeyBinding;
};

#endif
