#include "MenuState.hpp"

#include "../../Utility/Utility.hpp"
#include "../GUI/Button/Button.hpp"

MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context) {
    sf::Texture& texture = context.textures->get(Textures::ID::MenuBackground);
    sf::Font& font = context.fonts->get(Fonts::ID::Dosis);
    sf::Vector2f windowSize(context.window->getSize());

    mBackgroundSprite.setTexture(texture);
    mBackgroundSprite.setScale(
        windowSize.x / texture.getSize().x, windowSize.y / texture.getSize().y
    );

    auto playButton =
        std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    playButton->setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 30.f);
    playButton->setText("Play");
    playButton->setCallback([this]() {
        requestStackPop();
        requestStackPush(States::ID::Game);
    });

    // setting button

    auto exitButton =
        std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    exitButton->setPosition(windowSize.x / 2.f, windowSize.y / 2.f + 30.f);
    exitButton->setText("Exit");
    exitButton->setCallback([this]() { requestStackPop(); });

    mGUIContainer.pack(playButton);
    // mGUIContainer.pack(settingsButton);
    mGUIContainer.pack(exitButton);
}

void MenuState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.draw(mBackgroundSprite);

    window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time) { return true; }

bool MenuState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return false;  // false means that the event will be propagated to the next
                   // state
}
