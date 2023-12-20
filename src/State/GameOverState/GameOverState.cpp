#include "GameOverState.hpp"

#include "../../Utility/Utility.hpp"

GameOverState::GameOverState(StateStack& stack, Context context)
    : State(stack, context),
      mElapsedTime(sf::Time::Zero),
      mGameOverText(
          "Game Over!", context.fontHolder->get(Fonts::ID::Dosis), 70
      ) {
    sf::Vector2f windowSize(context.window->getSize());
    centerOrigin(mGameOverText);
    mGameOverText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 120.f);
}

void GameOverState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize());

    window.draw(backgroundShape);
    window.draw(mGameOverText);
}

bool GameOverState::update(sf::Time deltaTime) {
    mElapsedTime += deltaTime;

    if (mElapsedTime.asSeconds() >= 1.f) {
        requestStateClear();
        requestStackPush(States::ID::Menu);
    }

    return false;
}

bool GameOverState::handleEvent(const sf::Event& event) { return false; }
