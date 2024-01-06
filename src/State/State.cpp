#include "State.hpp"

#include "../StateStack/StateStack.hpp"

State::Context::Context(
    sf::RenderWindow& window, TextureHolder& textureHolder,
    FontHolder& fontHolder, PlayerSettings& playerSettings1,
    PlayerSettings& playerSettings2, PowerUpSettings& powerUpSettings1,
    PowerUpSettings& powerUpSettings2
)
    : window(&window),
      textureHolder(&textureHolder),
      fontHolder(&fontHolder),
      playerSettings1(&playerSettings1),
      playerSettings2(&playerSettings2),
      powerUpSettings1(&powerUpSettings1),
      powerUpSettings2(&powerUpSettings2) {}

State::State(StateStack& stack, Context context)
    : mStack(&stack), mContext(context) {}

State::~State() {}

void State::requestStackPush(States::ID stateID) { mStack->pushState(stateID); }

void State::requestStackPop() { mStack->popState(); }

void State::requestStateClear() { mStack->clearStates(); }

State::Context State::getContext() const { return mContext; }
