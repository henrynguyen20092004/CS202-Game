#include "Program.hpp"

#include "../Global/Global.hpp"
#include "../State/GameOverState/GameOverState.hpp"
#include "../State/GameState/GameState.hpp"
#include "../State/MenuState/MenuState.hpp"
#include "../State/PauseState/PauseState.hpp"
#include "../State/SelectPlayerState/SelectPlayerState.hpp"
#include "../State/SettingsState/SettingsState.hpp"
#include "../State/TitleState/TitleState.hpp"

Program::Program()
    : mWindow(
          sf::VideoMode(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT),
          "Crossy Road Gameplay", sf::Style::Close
      ),
      mPlayerSettings2(true),
      mPowerUpSettings2(true),
      mStateStack(State::Context(
          mWindow, mTextureHolder, mFontHolder, mPlayerSettings1,
          mPlayerSettings2, mPowerUpSettings1, mPowerUpSettings2
      )) {
    mWindow.setKeyRepeatEnabled(false);
    loadTextures();
    loadFonts();
    registerStates();

    mStateStack.pushState(States::ID::Title);
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

    mTextureHolder.load(Textures::ID::Halo, "assets/Textures/Halo.png");

    mTextureHolder.load(
        Textures::ID::TitleBackground, "assets/Textures/TitleBackground.jpg"
    );
    mTextureHolder.load(
        Textures::ID::MenuBackground, "assets/Textures/MenuBackground.png"
    );

    mTextureHolder.load(Textures::ID::Car, "assets/Textures/Car.png");
    mTextureHolder.load(Textures::ID::Train, "assets/Textures/Train.png");

    mTextureHolder.load(Textures::ID::Cat, "assets/Textures/Cat.png");
    mTextureHolder.load(Textures::ID::Elephant, "assets/Textures/Elephant.png");
    mTextureHolder.load(Textures::ID::Phoenix, "assets/Textures/Phoenix.png");
    mTextureHolder.load(
        Textures::ID::PolarBear, "assets/Textures/PolarBear.png"
    );
    mTextureHolder.load(Textures::ID::Pug, "assets/Textures/Pug.png");

    mTextureHolder.load(Textures::ID::Rock, "assets/Textures/Rock.png");
    mTextureHolder.load(Textures::ID::Tree, "assets/Textures/Tree.png");
    mTextureHolder.load(Textures::ID::Log, "assets/Textures/Log.png");
    mTextureHolder.load(
        Textures::ID::RailwaySignal, "assets/Textures/RailwaySignal.png"
    );
    mTextureHolder.load(
        Textures::ID::TrafficLight, "assets/Textures/TrafficLight.png"
    );

    mTextureHolder.load(
        Textures::ID::VehicleLane, "assets/Textures/VehicleLane.png"
    );
    mTextureHolder.load(
        Textures::ID::TrainLane, "assets/Textures/TrainLane.png"
    );
    mTextureHolder.load(
        Textures::ID::ObstacleLane, "assets/Textures/ObstacleLane.png"
    );
    mTextureHolder.load(Textures::ID::River, "assets/Textures/River.png");

    mTextureHolder.load(
        Textures::ID::ButtonNormal, "assets/Textures/ButtonNormal2.png"
    );
    mTextureHolder.load(
        Textures::ID::ButtonSelected, "assets/Textures/ButtonSelected2.png"
    );
    mTextureHolder.load(
        Textures::ID::ButtonPressed, "assets/Textures/ButtonPressed2.png"
    );
    mTextureHolder.load(
        Textures::ID::PlayerChoice1, "assets/Textures/BlackNinja.png"
    );
    mTextureHolder.load(
        Textures::ID::PlayerChoice2, "assets/Textures/BlueNinja.png"
    );
}

void Program::loadFonts() {
    mFontHolder.load(Fonts::ID::Dosis, "assets/Fonts/Dosis.ttf");
    mFontHolder.load(Fonts::ID::Pacifico, "assets/Fonts/Pacifico-Regular.ttf");
    mFontHolder.load(Fonts::ID::VTV323, "assets/Fonts/VT323-Regular.ttf");
}

void Program::registerStates() {
    mStateStack.registerState<TitleState>(States::ID::Title);
    mStateStack.registerState<MenuState>(States::ID::Menu);
    mStateStack.registerState<SettingsState>(States::ID::Settings);
    mStateStack.registerState<GameState>(States::ID::Game);
    mStateStack.registerState<GameState>(States::ID::MultiplayerGame, true);
    mStateStack.registerState<PauseState>(States::ID::Pause);
    mStateStack.registerState<SelectPlayerState>(
        States::ID::SelectMultiplayer, 0
    );
    mStateStack.registerState<SelectPlayerState>(States::ID::SelectPlayer1, 1);
    mStateStack.registerState<SelectPlayerState>(States::ID::SelectPlayer2, 2);
    mStateStack.registerState<GameOverState>(States::ID::GameOver);
    mStateStack.registerState<GameOverState>(
        States::ID::MultiplayerGameOver, true
    );
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
