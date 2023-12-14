#include "Program.hpp"

#include "../Global/Global.hpp"
#include "../State/GameState/GameState.hpp"
#include "../State/MenuState/MenuState.hpp"

Program::Program()
    : mWindow(
          sf::VideoMode(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT), "CSG",
          sf::Style::Close
      ),
      mStateStack(State::Context(mWindow, mTextureHolder, mFontHolder)) {
    loadTextures();
    loadFonts();
    registerStates();

    mStateStack.pushState(States::ID::Menu);
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
    mTextureHolder.load(Textures::ID::Player, "assets/Textures/Player.png");
    mTextureHolder.load(
        Textures::ID::Background, "assets/Textures/Background.png"
    );
    mTextureHolder.load(
        Textures::ID::VehicleLane, "assets/Textures/VehicleLane.png"
    );
    mTextureHolder.load(Textures::ID::Car, "assets/Textures/Car.png");
    mTextureHolder.load(
        Textures::ID::MenuBackground, "assets/Textures/MenuBackground.png"
    );
    mTextureHolder.load(
        Textures::ID::ButtonNormal, "assets/Textures/ButtonNormal.png"
    );
    mTextureHolder.load(
        Textures::ID::ButtonSelected, "assets/Textures/ButtonSelected.png"
    );
    mTextureHolder.load(
        Textures::ID::ButtonPressed, "assets/Textures/ButtonPressed.png"
    );
}

void Program::loadFonts() {
    mFontHolder.load(Fonts::ID::Dosis, "assets/Fonts/Dosis.ttf");
}

void Program::registerStates() {
    mStateStack.registerState<MenuState>(States::ID::Menu);
    mStateStack.registerState<GameState>(States::ID::Game);
    //      mStateStack.registerState<PauseState>(States::ID::Pause);
    //      mStateStack.registerState<TitleState>(States::ID::Title);
    //      mStateStack.registerState<LoadingState>(States::ID::Loading);
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
