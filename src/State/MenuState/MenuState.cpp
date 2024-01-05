#include "MenuState.hpp"

#include "../../Utility/Utility.hpp"
#include "../GUI/Button/Button.hpp"

MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context),
      mTitleText(
          "Crossy Road", context.fontHolder->get(Fonts::ID::VTV323), 100
      ) {
    sf::Texture& backgroundTexture =
        context.textureHolder->get(Textures::ID::MenuBackground);
    mBackgroundSprite.setTexture(backgroundTexture);

    sf::Vector2f windowSize(context.window->getSize());
    mBackgroundSprite.setScale(
        windowSize.x / backgroundTexture.getSize().x,
        windowSize.y / backgroundTexture.getSize().y
    );

    centerOrigin(mTitleText);
    mTitleText.setFillColor(sf::Color(0, 255, 127));
    mTitleText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 180.f);

    auto playButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Play"
    );
    playButton->setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 60.f);
    playButton->setCallback([this]() {
        requestStackPop();
        requestStackPush(States::ID::Game);
    });

    auto mutiplayerButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Mutiplayer"
    );
    mutiplayerButton->setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
    mutiplayerButton->setCallback([this]() {
        requestStackPop();
        requestStackPush(States::ID::MultiplayerGame);
    });

    auto settingButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Setting"
    );
    settingButton->setPosition(windowSize.x / 2.f, windowSize.y / 2.f + 60.f);
    settingButton->setCallback([this]() {
        requestStackPush(States::ID::Settings);
    });

    auto exitButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Exit"
    );
    exitButton->setPosition(windowSize.x / 2.f, windowSize.y / 2.f + 120.f);
    exitButton->setCallback([this]() { requestStackPop(); });

    mGUIContainer.addComponent(playButton);
    mGUIContainer.addComponent(mutiplayerButton);
    mGUIContainer.addComponent(settingButton);
    mGUIContainer.addComponent(exitButton);
}

bool MenuState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event, *getContext().window);
    return false;
}

bool MenuState::update(sf::Time deltaTime) { return true; }

void MenuState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.draw(mBackgroundSprite);
    window.draw(mTitleText);
    window.draw(mGUIContainer);
}
