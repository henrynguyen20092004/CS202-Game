#include "GameState.hpp"

GameState::GameState(StateStack& stack, Context context)
    : State(stack, context), mWorld(*context.window, *context.textureHolder) {}

void GameState::draw() { mWorld.draw(); }

bool GameState::update(sf::Time deltaTime) {
    mWorld.update(deltaTime);
    return true;
}

bool GameState::handleEvent(const sf::Event& event) {
    mWorld.handleEvent(event);
    return true;
}
