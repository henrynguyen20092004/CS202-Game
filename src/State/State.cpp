#include "State.hpp"

#include "../StateStack/StateStack.hpp"

State::Context::Context(
    sf::RenderWindow& window, TextureHolder& textureHolder,
    FontHolder& fontHolder, PlayerSettings& playerSettings,
    PowerUpSettings& powerUpSettings
)
    : window(&window),
      textureHolder(&textureHolder),
      fontHolder(&fontHolder),
      playerSettings(&playerSettings),
      powerUpSettings(&powerUpSettings) {}

State::State(StateStack& stack, Context context)
    : mStack(&stack), mContext(context) {}

State::~State() {}

void State::requestStackPush(States::ID stateID) { mStack->pushState(stateID); }

void State::requestStackPop() { mStack->popState(); }

void State::requestStateClear() { mStack->clearStates(); }

State::Context State::getContext() const { return mContext; }
