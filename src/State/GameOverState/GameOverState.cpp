#include "GameOverState.hpp"

#include <iostream>
#include <string>

#include "../../Global/Global.hpp"
#include "../../Score/Score.hpp"
#include "../../Utility/Utility.hpp"
#include "../GUI/Button/Button.hpp"

GameOverState::GameOverState(
    StateStack& stack, Context context, bool isMultiplayer, int deadPlayer
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
      mWinnerText("", context.fontHolder->get(Fonts::ID::VTV323), 40),
      mIsMultiplayer(isMultiplayer),
      mDeadPlayer(deadPlayer) {
    context.mHighScore->rankScore(Global::SCORE);

    sf::Vector2f windowSize(context.window->getSize());
    centerOrigin(mGameOverText);
    mGameOverText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 160.f);

    if (!isMultiplayer) {
        centerOrigin(mCurrentScoreText);
        mCurrentScoreText.setPosition(
            windowSize.x / 2.f, windowSize.y / 2.f - 80.f
        );
    }

    auto replayButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Replay"
    );
    replayButton->setPosition(windowSize.x / 2, windowSize.y / 2.f);
    replayButton->setCallback([this, isMultiplayer]() {
        requestStateClear();
        requestStackPush(
            isMultiplayer ? States::ID::NewMultiplayerGame
                          : States::ID::NewSingleGame
        );
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
    window.draw(mIsMultiplayer ? mWinnerText : mCurrentScoreText);
    window.draw(mGUIContainer);
}

bool GameOverState::update(sf::Time deltaTime) {
    if (mIsMultiplayer) {
        mWinnerText.setString(
            "Player " + std::to_string(mDeadPlayer == 0 ? 2 : 1) + " wins!"
        );

        sf::Vector2f windowSize(getContext().window->getSize());
        centerOrigin(mWinnerText);
        mWinnerText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 80.f);
    }

    return false;
}

bool GameOverState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event, *getContext().window);
    return false;
}
