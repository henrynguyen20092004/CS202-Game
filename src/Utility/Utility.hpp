#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <SFML/Graphics.hpp>

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);
void centerOriginTextForUnpressedButton(sf::Text& text);
void centerOriginTextForPressedButton(sf::Text& text);
std::string toString(sf::Keyboard::Key key);

#endif
