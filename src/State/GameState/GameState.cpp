#include "GameState.hpp"

#include "../../Global/Global.hpp"
#include "../PauseState/PauseState.hpp"

GameState::GameState(
    StateStack& stack, Context context, bool isMultiplayer, bool isLoading
)
    : State(stack, context),
      mWorld(context, isMultiplayer, isLoading),
      isMultiplayer(isMultiplayer),
      isLoading(isLoading) {}

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
    int deadPlayer = mWorld.getDeadPlayer();

    if (deadPlayer != -1) {
        requestStackPush(
            isMultiplayer
                ? (deadPlayer == 0 ? States::ID::MultiplayerGameOverDead1
                                   : States::ID::MultiplayerGameOverDead2)
                : States::ID::GameOver
        );
    }

    return true;
}

void GameState::draw() { mWorld.draw(); }
