#include "Global.hpp"

#include <SFML/Graphics.hpp>

#define DESKTOP_MODE sf::VideoMode::getDesktopMode()
#define WINDOW_DESKTOP_RATIO 0.75f

int Global::WINDOW_WIDTH = DESKTOP_MODE.width * WINDOW_DESKTOP_RATIO;
int Global::WINDOW_HEIGHT = DESKTOP_MODE.height * WINDOW_DESKTOP_RATIO;