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
      mWorld(mWindow),
      mTextures(),
      mFonts(),
      mStateStack(State::Context(mWindow, mTextures, mFonts)) {
    mFonts.load(Fonts::ID::Main, "assets/Fonts/Dosis.ttf");
    mTextures.load(
        Textures::ID::TitleScreen, "assets/Textures/TitleScreen.png"
    );
    // how to scale the title screen?
    registerState();
    mStateStack.pushState(States::ID::Menu);
    // mWindow.setKeyRepeatEnabled(false);
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
        }

        draw();
    }
}

void Program::handleEvent(sf::Event& event) {
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            mWindow.close();
        }

        // mWorld.handleEvent(event);
    }
}

void Program::update() {
    // mWorld.update(TIME_PER_FRAME);
    mStateStack.update(TIME_PER_FRAME);
}

void Program::draw() {
    mWindow.clear(sf::Color::Black);
    // mWorld.draw();
    mStateStack.draw();
    mWindow.display();
}

void Program::registerState() {
    mStateStack.registerState<MenuState>(States::ID::Menu);
    mStateStack.registerState<GameState>(States::ID::Game);
    //     mStateStack.registerState<PauseState>(States::ID::Pause);
    //     mStateStack.registerState<TitleState>(States::ID::Title);
    //     mStateStack.registerState<LoadingState>(States::ID::Loading);
}
