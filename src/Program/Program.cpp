#include "Program.hpp"

Program::Program()
    : mWindow(sf::VideoMode(1440, 810), "CSG", sf::Style::Close) {}

Program::~Program() {}

void Program::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate;
    sf::Event event;

    while (mWindow.isOpen()) {
        processEvents(event);
        timeSinceLastUpdate += clock.restart();

        while (timeSinceLastUpdate > TIME_PER_FRAME) {
            timeSinceLastUpdate -= TIME_PER_FRAME;
            processEvents(event);
            update();
        }

        render();
    }
}

void Program::processEvents(sf::Event &event) {
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

void Program::update() {}

void Program::render() {
    mWindow.clear(sf::Color::White);
    mWindow.display();
}
