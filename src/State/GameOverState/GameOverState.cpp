#include "GameOverState.hpp"

#include <string>

#include "../../Global/Global.hpp"
#include "../../Score/Score.hpp"
#include "../../Utility/Utility.hpp"
#include "../GUI/Button/Button.hpp"

GameOverState::GameOverState(
    StateStack& stack, Context context, bool isMultiplayer
)
    : State(stack, context),
      mElapsedTime(sf::Time::Zero),
      mGameOverText(
          "Game Over!", context.fontHolder->get(Fonts::ID::VTV323), 80
      ),
      mCurrentScoreText(
          "Your Current Score: " + std::to_string(Global::SCORE),
          context.fontHolder->get(Fonts::ID::VTV323), 40
      ),
      mHighestScoreText(
          "Your Highest Score: ", context.fontHolder->get(Fonts::ID::VTV323), 30
      ) {
    sf::Vector2f windowSize(context.window->getSize());
    // Todo: Create data table to display highest score
    centerOrigin(mGameOverText);
    mGameOverText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 160.f);

    centerOrigin(mCurrentScoreText);
    mCurrentScoreText.setPosition(
        windowSize.x / 2.f, windowSize.y / 2.f - 80.f
    );

    auto replayButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Replay"
    );
    replayButton->setPosition(windowSize.x / 2, windowSize.y / 2.f);
    replayButton->setCallback([this, isMultiplayer]() {
        requestStateClear();

        if (isMultiplayer) {
            requestStackPush(States::ID::MultiplayerGame);
        } else {
            requestStackPush(States::ID::Game);
        }
    });

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
    window.draw(mCurrentScoreText);
    // window.draw(mHighestScoreText);
    window.draw(mGUIContainer);
}

bool GameOverState::update(sf::Time deltaTime) { return false; }

bool GameOverState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event, *getContext().window);
    return false;
}
