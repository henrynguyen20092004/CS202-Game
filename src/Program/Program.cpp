#include "Program.hpp"

#define DESKTOP_MODE sf::VideoMode::getDesktopMode()
#define WINDOW_DESKTOP_RATIO 0.75f

Program::Program()
    : mWindow(
          sf::VideoMode(
              DESKTOP_MODE.width * WINDOW_DESKTOP_RATIO,
              DESKTOP_MODE.height * WINDOW_DESKTOP_RATIO
          ),
          "CSG", sf::Style::Close
      ),
      mWorld(mWindow) {}

Program::~Program() {}

void Program::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate;
    sf::Event event;

    while (mWindow.isOpen()) {
        handleEvent(event);
        timeSinceLastUpdate += clock.restart();

        while (timeSinceLastUpdate > TIME_PER_FRAME) {
            timeSinceLastUpdate -= TIME_PER_FRAME;
            handleEvent(event);
            update();
        }

        draw();
    }
}

void Program::handleEvent(sf::Event& event) {
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            mWindow.close();
        }

        mWorld.handleEvent(event);
    }
}

void Program::update() { mWorld.update(TIME_PER_FRAME); }

void Program::draw() {
    mWindow.clear(sf::Color::White);
    mWorld.draw();
    mWindow.display();
}
