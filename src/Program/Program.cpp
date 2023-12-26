#include "Program.hpp"

#include "../Global/Global.hpp"
#include "../State/GameOverState/GameOverState.hpp"
#include "../State/GameState/GameState.hpp"
#include "../State/MenuState/MenuState.hpp"
#include "../State/PauseState/PauseState.hpp"

Program::Program()
    : mWindow(
          sf::VideoMode(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT),
          "Crossy Road Gameplay", sf::Style::Close
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
        Textures::ID::MenuBackground, "assets/Textures/MenuBackground.png"
    );

    mTextureHolder.load(Textures::ID::CarLeft, "assets/Textures/CarLeft.png");
    mTextureHolder.load(Textures::ID::CarRight, "assets/Textures/CarRight.png");
    mTextureHolder.load(
        Textures::ID::TrainLeft, "assets/Textures/TrainLeft.png"
    );
    mTextureHolder.load(
        Textures::ID::TrainRight, "assets/Textures/TrainRight.png"
    );

    mTextureHolder.load(Textures::ID::Cat, "assets/Textures/Cat.png");
    mTextureHolder.load(Textures::ID::Elephant, "assets/Textures/Elephant.png");
    mTextureHolder.load(Textures::ID::Phoenix, "assets/Textures/Phoenix.png");
    mTextureHolder.load(
        Textures::ID::PolarBear, "assets/Textures/PolarBear.png"
    );
    mTextureHolder.load(Textures::ID::Pug, "assets/Textures/Pug.png");

    mTextureHolder.load(Textures::ID::Rock, "assets/Textures/Rock.png");

    mTextureHolder.load(
        Textures::ID::VehicleLane, "assets/Textures/VehicleLane.png"
    );
    mTextureHolder.load(
        Textures::ID::TrainLane, "assets/Textures/TrainLane.png"
    );
    mTextureHolder.load(
        Textures::ID::ObstacleLane, "assets/Textures/ObstacleLane.png"
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
    mTextureHolder.load(
        Textures::ID::TrafficLight, "assets/Textures/TrafficLight.png"
    );
}

void Program::loadFonts() {
    mFontHolder.load(Fonts::ID::Dosis, "assets/Fonts/Dosis.ttf");
    mFontHolder.load(Fonts::ID::Pacifico, "assets/Fonts/Pacifico-Regular.ttf");
}

void Program::registerStates() {
    mStateStack.registerState<MenuState>(States::ID::Menu);
    mStateStack.registerState<GameState>(States::ID::Game);
    mStateStack.registerState<PauseState>(States::ID::Pause);
    //     mStateStack.registerState<TitleState>(States::ID::Title);
    //     mStateStack.registerState<LoadingState>(States::ID::Loading);
    mStateStack.registerState<GameOverState>(States::ID::GameOver);
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
