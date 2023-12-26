#include "TitleState.hpp"

#include "../../Utility/Utility.hpp"

TitleState::TitleState(StateStack& stack, Context context)
    : State(stack, context),
      mShowText(true),
      mText(
          "Press any key to start",
          context.fontHolder->get(Fonts::ID::Pacifico), 20
      ) {
    mBackgroundSprite.setTexture(
        context.textureHolder->get(Textures::ID::TitleBackground)
    );

    mBackgroundSprite.setScale(
        context.window->getView().getSize().x /
            mBackgroundSprite.getLocalBounds().width,
        context.window->getView().getSize().y /
            mBackgroundSprite.getLocalBounds().height
    );

    centerOrigin(mText);
    mText.setPosition(
        context.window->getView().getSize().x / 2.f,
        context.window->getView().getSize().y / 2.f + 120.f
    );
}

void TitleState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.draw(mBackgroundSprite);
    if (mShowText) {
        window.draw(mText);
    }
}

bool TitleState::update(sf::Time deltaTime) {
    mTextEffectTime += deltaTime;
    if (mTextEffectTime >= sf::seconds(0.5f)) {
        mShowText = !mShowText;
        mTextEffectTime = sf::Time::Zero;
    }
    return true;
}

bool TitleState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        requestStackPop();
        requestStackPush(States::ID::Menu);
    }

    return true;
}
