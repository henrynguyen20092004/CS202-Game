#include "SelectPlayerState.hpp"

#include "../../Utility/Utility.hpp"
#include "../GUI/Button/Button.hpp"

SelectPlayerState::SelectPlayerState(
    StateStack& stack, Context context, SelectPlayerState::Type selectState
)
    : State(stack, context),
      mChoiceCount(
          static_cast<int>(Textures::ID::PlayerChoice6) -
          static_cast<int>(Textures::ID::PlayerChoice1) + 1
      ),
      mCurrentChoiceIndex(0),
      mSelectState(selectState),
      mTitleText("Player 1", context.fontHolder->get(Fonts::ID::VTV323), 80),
      mDirectionButtonsContainer(true) {
    sf::Vector2f windowSize(context.window->getSize());
    sf::Texture& backgroundTexture =
        context.textureHolder->get(Textures::ID::MenuBackground);

    mBackgroundSprite.setTexture(backgroundTexture);
    mBackgroundSprite.setScale(
        windowSize.x / backgroundTexture.getSize().x,
        windowSize.y / backgroundTexture.getSize().y
    );

    centerOrigin(mTitleText);
    mTitleText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 80.f);

    if (mSelectState == SelectPlayerState::Type::Player2Multi) {
        mTitleText.setString("Player 2");
    }

    sf::Texture& playerChoiceTexture =
        context.textureHolder->get(Textures::ID::PlayerChoice1);
    mPlayerChoiceSprite.setTexture(playerChoiceTexture);
    mPlayerChoiceSprite.setTextureRect(sf::IntRect(60, 0, 60, 60));
    centerOrigin(mPlayerChoiceSprite);
    mPlayerChoiceSprite.setScale(2.f, 2.f);
    mPlayerChoiceSprite.setPosition(
        windowSize.x / 2.f, windowSize.y / 2.f + 60.f
    );

    auto leftButtonNormal = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "", true, true
    );
    leftButtonNormal->setPosition(
        windowSize.x / 2.f - 100.f, windowSize.y / 2.f + 60.f
    );
    leftButtonNormal->setCallback([this]() {
        mCurrentChoiceIndex =
            (mCurrentChoiceIndex - 1 + mChoiceCount) % mChoiceCount;
        updatePlayerChoiceSprite();
    });

    auto rightButtonNormal = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "", true, false
    );
    rightButtonNormal->setPosition(
        windowSize.x / 2.f + 100.f, windowSize.y / 2.f + 60.f
    );
    rightButtonNormal->setCallback([this]() {
        mCurrentChoiceIndex = (mCurrentChoiceIndex + 1) % mChoiceCount;
        updatePlayerChoiceSprite();
    });

    auto acceptButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Accept"
    );
    acceptButton->setPosition(windowSize.x / 2.f, windowSize.y / 2.f + 180.f);
    acceptButton->setCallback([this, context]() {
        switch (mSelectState) {
            case SelectPlayerState::Type::Player1Single:
                context.textureHolder->load(
                    Textures::ID::Player1SelectedChoiceSingle,
                    static_cast<Textures::ID>(
                        static_cast<int>(Textures::ID::PlayerChoice1) +
                        mCurrentChoiceIndex
                    )
                );
                requestStackPop();
                requestStackPush(States::ID::NewSingleGame);
                break;

            case SelectPlayerState::Type::Player1Multi:
                context.textureHolder->load(
                    Textures::ID::Player1SelectedChoiceMulti,
                    static_cast<Textures::ID>(
                        static_cast<int>(Textures::ID::PlayerChoice1) +
                        mCurrentChoiceIndex
                    )
                );
                requestStackPop();
                requestStackPush(States::ID::SelectPlayer2Multi);
                break;

            case SelectPlayerState::Type::Player2Multi:
                context.textureHolder->load(
                    Textures::ID::Player2SelectedChoiceMulti,
                    static_cast<Textures::ID>(
                        static_cast<int>(Textures::ID::PlayerChoice1) +
                        mCurrentChoiceIndex
                    )
                );
                requestStackPop();
                requestStackPush(States::ID::NewMultiplayerGame);
                break;

            default:
                break;
        }
    });

    auto backToMenuButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Back to Menu"
    );
    backToMenuButton->setCallback([this]() {
        requestStackClear();
        requestStackPush(States::ID::Menu);
    });
    backToMenuButton->setPosition(250.f, 50.f);

    mDirectionButtonsContainer.addComponent(leftButtonNormal);
    mDirectionButtonsContainer.addComponent(rightButtonNormal);

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

    mDirectionButtonsContainer.handleEvent(event, *getContext().window);
    mGUIContainer.handleEvent(event, *getContext().window);
    return false;
}

bool SelectPlayerState::update(sf::Time deltaTime) { return true; }

void SelectPlayerState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.draw(mBackgroundSprite);
    window.draw(mPlayerChoiceSprite);
    window.draw(mTitleText);
    window.draw(mDirectionButtonsContainer);
    window.draw(mGUIContainer);
}

void SelectPlayerState::updatePlayerChoiceSprite() {
    sf::Texture& playerChoiceTexture =
        getContext().textureHolder->get(static_cast<Textures::ID>(
            static_cast<int>(Textures::ID::PlayerChoice1) + mCurrentChoiceIndex
        ));

    mPlayerChoiceSprite.setTexture(playerChoiceTexture);
}
