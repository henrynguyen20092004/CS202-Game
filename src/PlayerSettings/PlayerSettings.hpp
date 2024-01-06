#ifndef PLAYER_SETTINGS_HPP
#define PLAYER_SETTINGS_HPP

#include <SFML/Window.hpp>
#include <map>

#include "../Identifier/Identifier.hpp"

class PlayerSettings {
   public:
    PlayerSettings(bool isPlayer2 = false);

    void assignKey(sf::Keyboard::Key key, Directions::ID direction);
    Directions::ID getDirection(sf::Keyboard::Key key) const;
    sf::Keyboard::Key getAssignedKey(Directions::ID direction) const;

    void setToDefault(bool isPlayer2 = false);

    void save(std::ofstream& fout) const;
    void load(std::ifstream& fin);

   private:
    std::map<sf::Keyboard::Key, Directions::ID> mKeyBinding;
};

#endif
