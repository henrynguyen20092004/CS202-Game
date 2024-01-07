#include "GameState.hpp"

#include "../../Global/Global.hpp"
#include "../PauseState/PauseState.hpp"

GameState::GameState(StateStack& stack, Context context, bool isMultiplayer)
    : State(stack, context),
      mWorld(context, isMultiplayer),
      isMultiplayer(isMultiplayer) {
    Global::SCORE = 0;
}

bool GameState::handleEvent(const sf::Event& event) {
    mWorld.handleEvent(event);

    if ((event.type == sf::Event::KeyPressed &&
         event.key.code == sf::Keyboard::Escape) ||
        event.type == sf::Event::LostFocus) {
        requestStackPush(States::ID::Pause);
    }

    return true;
}

bool GameState::update(sf::Time deltaTime) {
    mWorld.update(deltaTime);

    if (!mWorld.isPlayerAlive()) {
        if (isMultiplayer) {
            requestStackPush(States::ID::MultiplayerGameOver);
        } else {
            requestStackPush(States::ID::GameOver);
        }
    }

    return true;
}

void GameState::draw() { mWorld.draw(); }
