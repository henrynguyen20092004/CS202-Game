#include "Program.hpp"

#include "../State/GameState/GameState.hpp"

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
      mStateStack(State::Context(mWindow, mTextures, mFonts)) {
    loadTextures();
    loadFonts();
    registerState();

    mStateStack.pushState(States::ID::Game);
}

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

            if (mStateStack.isEmpty()) {
                mWindow.close();
            }
        }

        draw();
    }
}

void Program::loadTextures() {
    mTextures.load(Textures::ID::Player, "assets/Textures/Player.png");
    mTextures.load(Textures::ID::Background, "assets/Textures/Background.png");
}

void Program::loadFonts() {
    mFonts.load(Fonts::ID::Main, "assets/Fonts/Dosis.ttf");
}

void Program::registerState() {
    mStateStack.registerState<GameState>(States::ID::Game);
    //     mStateStack.registerState<MenuState>(States::ID::Menu);
    //     mStateStack.registerState<PauseState>(States::ID::Pause);
    //     mStateStack.registerState<TitleState>(States::ID::Title);
    //     mStateStack.registerState<LoadingState>(States::ID::Loading);
}

void Program::handleEvent(sf::Event& event) {
    while (mWindow.pollEvent(event)) {
        mStateStack.handleEvent(event);

        if (event.type == sf::Event::Closed) {
            mWindow.close();
        }
    }
}

void Program::update() { mStateStack.update(TIME_PER_FRAME); }

void Program::draw() {
    mWindow.clear(sf::Color::Black);
    mStateStack.draw();
    mWindow.display();
}
