#include "SelectPlayerState.hpp"

#include "../../Utility/Utility.hpp"
#include "../GUI/Button/Button.hpp"

SelectPlayerState::SelectPlayerState(StateStack& stack, Context context)
    : State(stack, context),
      mChoiceCount(
          static_cast<int>(Textures::ID::PlayerSelectedChoice) -
          static_cast<int>(Textures::ID::PlayerChoice1)
      ),
      mCurrentChoiceIndex(0) {
    sf::Texture& backgroundTexture =
        context.textureHolder->get(Textures::ID::MenuBackground);
    mBackgroundSprite.setTexture(backgroundTexture);

    sf::Vector2f windowSize(context.window->getSize());
    mBackgroundSprite.setScale(
        windowSize.x / backgroundTexture.getSize().x,
        windowSize.y / backgroundTexture.getSize().y
    );

    sf::Texture& playerChoiceTexture =
        context.textureHolder->get(Textures::ID::PlayerChoice1);
    mPlayerChoiceSprite.setTexture(playerChoiceTexture);
    mPlayerChoiceSprite.setTextureRect(sf::IntRect(60, 0, 60, 60));
    mPlayerChoiceSprite.setScale(2.f, 2.f);
    centerOrigin(mPlayerChoiceSprite);
    mPlayerChoiceSprite.setPosition(
        windowSize.x / 2.f, windowSize.y / 2.f + 60.f
    );

    auto acceptButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Accept"
    );
    acceptButton->setPosition(windowSize.x / 2.f, windowSize.y / 2.f + 180.f);
    acceptButton->setCallback([this, context]() {
        context.textureHolder->load(
            Textures::ID::PlayerSelectedChoice,
            static_cast<Textures::ID>(
                static_cast<int>(Textures::ID::PlayerChoice1) +
                mCurrentChoiceIndex
            )
        );
        requestStackPop();
        requestStackPush(States::ID::Game);
    });

    auto backToMenuButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Back to Menu"
    );
    backToMenuButton->setCallback([this]() {
        requestStateClear();
        requestStackPush(States::ID::Menu);
    });
    backToMenuButton->setPosition(250.f, 50.f);

    mGUIContainer.addComponent(acceptButton);
    mGUIContainer.addComponent(backToMenuButton);
}

bool SelectPlayerState::handleEvent(const sf::Event& event) {
    bool isChoiceChanged = false;
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Left:
                mCurrentChoiceIndex =
                    (mCurrentChoiceIndex - 1 + mChoiceCount) % mChoiceCount;
                break;
            case sf::Keyboard::Right:
                mCurrentChoiceIndex = (mCurrentChoiceIndex + 1) % mChoiceCount;
                break;
            default:
                break;
        }
        isChoiceChanged = true;
    }

    if (isChoiceChanged) {
        updatePlayerChoiceSprite();
    }

    mGUIContainer.handleEvent(event, *getContext().window);
    return false;
}

bool SelectPlayerState::update(sf::Time deltaTime) { return true; }

void SelectPlayerState::updatePlayerChoiceSprite() {
    sf::Texture& playerChoiceTexture =
        getContext().textureHolder->get(static_cast<Textures::ID>(
            static_cast<int>(Textures::ID::PlayerChoice1) + mCurrentChoiceIndex
        ));

    mPlayerChoiceSprite.setTexture(playerChoiceTexture);
}

void SelectPlayerState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.draw(mBackgroundSprite);
    window.draw(mPlayerChoiceSprite);
    window.draw(mGUIContainer);
}
