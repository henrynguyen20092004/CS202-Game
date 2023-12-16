#include "MenuState.hpp"

#include "../../Utility/Utility.hpp"
#include "../GUI/Button/Button.hpp"

MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context) {
    sf::Texture& backgroundTexture =
        context.textureHolder->get(Textures::ID::MenuBackground);
    sf::Vector2f windowSize(context.window->getSize());

    mBackgroundSprite.setTexture(backgroundTexture);
    mBackgroundSprite.setScale(
        windowSize.x / backgroundTexture.getSize().x,
        windowSize.y / backgroundTexture.getSize().y
    );

    auto playButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Play"
    );
    playButton->setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 60.f);
    playButton->setCallback([this]() {
        requestStackPop();
        requestStackPush(States::ID::Game);
    });

    auto settingButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Setting"
    );
    settingButton->setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
    settingButton->setCallback([this]() {
        requestStackPop();
        requestStackPush(States::ID::Setting);
    });

    auto exitButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Exit"
    );
    exitButton->setPosition(windowSize.x / 2.f, windowSize.y / 2.f + 60.f);
    exitButton->setCallback([this]() { requestStackPop(); });

    mGUIContainer.addComponent(playButton);
    mGUIContainer.addComponent(settingButton);
    mGUIContainer.addComponent(exitButton);
}

bool MenuState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return false;
}

bool MenuState::update(sf::Time deltaTime) { return true; }

void MenuState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.draw(mBackgroundSprite);
    window.draw(mGUIContainer);
}
