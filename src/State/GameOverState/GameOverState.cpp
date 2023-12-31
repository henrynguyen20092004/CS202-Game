#include "GameOverState.hpp"

#include <string>

#include "../../Global/Global.hpp"
#include "../../Score/Score.hpp"
#include "../../Utility/Utility.hpp"
#include "../GUI/Button/Button.hpp"

GameOverState::GameOverState(StateStack& stack, Context context)
    : State(stack, context),
      mElapsedTime(sf::Time::Zero),
      mGameOverText(
          "Game Over!", context.fontHolder->get(Fonts::ID::Dosis), 70
      ),
      mScoreText(
          "Your Score:", context.fontHolder->get(Fonts::ID::Dosis), 30
      ) {
    sf::Vector2f windowSize(context.window->getSize());
    // Todo: Create data table to display current score and highest score
    centerOrigin(mGameOverText);
    mGameOverText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 140.f);

    centerOrigin(mScoreText);
    mScoreText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 80.f);

    auto backToMenuButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Back to menu"
    );
    backToMenuButton->setPosition(
        windowSize.x / 2.f, windowSize.y / 2.f + 60.f
    );
    backToMenuButton->setCallback([this]() {
        requestStateClear();
        requestStackPush(States::ID::Menu);
    });

    auto replayButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Replay"
    );
    replayButton->setPosition(windowSize.x / 2, windowSize.y / 2.f);
    replayButton->setCallback([this]() {
        requestStateClear();
        requestStackPush(States::ID::Game);
    });

    mGUIContainer.addComponent(replayButton);
    mGUIContainer.addComponent(backToMenuButton);
}

void GameOverState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize());

    window.draw(backgroundShape);
    window.draw(mGameOverText);
    window.draw(mScoreText);
    window.draw(mGUIContainer);
}

bool GameOverState::update(sf::Time deltaTime) { return false; }

bool GameOverState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event, *getContext().window);
    return false;
}
