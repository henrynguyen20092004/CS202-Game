#include "GameState.hpp"

#include "../PauseState/PauseState.hpp"

GameState::GameState(StateStack& stack, Context context)
    : State(stack, context), mWorld(context) {}

bool GameState::handleEvent(const sf::Event& event) {
    mWorld.handleEvent(event);

    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Escape) {
        requestStackPush(States::ID::Pause);
    }

    return true;
}

bool GameState::update(sf::Time deltaTime) {
    mWorld.update(deltaTime);
    if (!mWorld.isPlayerAlive()) {
        requestStackPush(States::ID::GameOver);
    }
    return true;
}

void GameState::draw() { mWorld.draw(); }
