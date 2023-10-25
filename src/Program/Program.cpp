#include "Program.hpp"

Program::Program()
    : mWindow(sf::VideoMode(1440, 810), "CSG", sf::Style::Close) {}

Program::~Program() {}

void Program::run() {
    while (mWindow.isOpen()) {
        handleEvent();
        mWindow.clear(sf::Color::White);
        mWindow.display();
    }
}

void Program::handleEvent() {
    sf::Event event;

    while (mWindow.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                mWindow.close();
                break;

            case sf::Event::KeyPressed:
                if (event.key.scancode == sf::Keyboard::Scancode::Escape) {
                    mWindow.close();
                }

                break;

            default:
                break;
        }
    }
}
