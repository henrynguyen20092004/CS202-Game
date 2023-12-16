#include "GameOverState.hpp"

#include "../../Utility/Utility.hpp"

GameOverState::GameOverState(StateStack& stack, Context context)
    : State(stack, context), mElapsedTime(sf::Time::Zero) {
    mGameOverText.setFont(context.fontHolder->get(Fonts::ID::Dosis));
    mGameOverText.setString("Game Over!");
    mGameOverText.setCharacterSize(70);
    centerOrigin(mGameOverText);
    mGameOverText.setPosition(context.window->getView().getSize() / 2.f);
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

    if (mElapsedTime.asSeconds() >= 3.f) {
        requestStateClear();
        requestStackPush(States::ID::Menu);
    }

    return false;
}

bool GameOverState::handleEvent(const sf::Event& event) { return false; }
