#include "GameState.hpp"

#include "../PauseState/PauseState.hpp"

GameState::GameState(StateStack& stack, Context context)
    : State(stack, context), mWorld(*context.window, *context.textureHolder) {}

void GameState::draw() { mWorld.draw(); }

bool GameState::update(sf::Time deltaTime) {
    mWorld.update(deltaTime);
    return true;
}

bool GameState::handleEvent(const sf::Event& event) {
    mWorld.handleEvent(event);
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Escape)
        requestStackPush(States::ID::Pause);
    return true;
}
