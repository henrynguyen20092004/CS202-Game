#include "HighScoreState.hpp"

#include "../../Utility/Utility.hpp"
#include "../GUI/Button/Button.hpp"

HighScoreState::HighScoreState(StateStack& stack, Context context)
    : State(stack, context),
      mHighScore(context.mHighScore),
      mTitleText(
          "High Score", context.fontHolder->get(Fonts::ID::VTV323), 100
      ) {
    sf::Texture& backgroundTexture =
        context.textureHolder->get(Textures::ID::SettingBackground);
    mBackgroundSprite.setTexture(backgroundTexture);

    sf::Vector2f windowSize(context.window->getSize());
    mBackgroundSprite.setScale(
        windowSize.x / backgroundTexture.getSize().x,
        windowSize.y / backgroundTexture.getSize().y
    );

    sf::Texture& frameTexture = context.textureHolder->get(Textures::ID::Frame);
    mFrameSprite.setTexture(frameTexture);
    centerOrigin(mFrameSprite);
    mFrameSprite.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
    mFrameSprite.setScale(800.f / frameTexture.getSize().x, 1.f);

    centerOrigin(mTitleText);
    mTitleText.setFillColor(sf::Color(196, 154, 108));
    mTitleText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 180.f);

    setText(windowSize);

    auto backToMenuButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Back to Menu"
    );
    backToMenuButton->setPosition(250.f, 50.f);
    backToMenuButton->setCallback([this]() {
        requestStateClear();
        requestStackPush(States::ID::Menu);
    });

    mGUIContainer.addComponent(backToMenuButton);
}

bool HighScoreState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event, *getContext().window);
    return false;
}

bool HighScoreState::update(sf::Time deltaTime) { return true; }

void HighScoreState::setText(sf::Vector2f windowSize) {
    std::vector<int> mHighScores = mHighScore->getHighScores();
    sf::Text text;

    text.setFont(getContext().fontHolder->get(Fonts::ID::VTV323));
    text.setCharacterSize(60);

    for (int i = 0; i < mHighScores.size(); i++) {
        text.setString(
            std::to_string(i + 1) + ".\t\t\t" + std::to_string(mHighScores[i])
        );
        text.setPosition(
            windowSize.x / 2.f - 200.f, windowSize.y / 2.f - 100.f + i * 50
        );
        mTexts.push_back(text);
    }
}

void HighScoreState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.draw(mBackgroundSprite);
    window.draw(mFrameSprite);
    window.draw(mTitleText);

    for (int i = 0; i < mTexts.size(); i++) {
        window.draw(mTexts[i]);
    }

    window.draw(mGUIContainer);
}
