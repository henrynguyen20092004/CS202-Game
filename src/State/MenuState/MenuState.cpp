#include "MenuState.hpp"

MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context), mOptionIndex(0) {
    sf::Texture& texture = context.textures->get(Textures::ID::MenuBackground);
    sf::Font& font = context.fonts->get(Fonts::ID::Main);
    sf::Vector2f windowSize(context.window->getSize());

    mBackgroundSprite.setTexture(texture);
    mBackgroundSprite.setScale(
        windowSize.x / texture.getSize().x, windowSize.y / texture.getSize().y
    );

    sf::Text playOption;
    playOption.setFont(font);
    playOption.setString("Play");
    centerOrigin(playOption);
    playOption.setPosition(windowSize / 2.f);
    mOptions.push_back(playOption);

    sf::Text exitOption;
    exitOption.setFont(font);
    exitOption.setString("Exit");
    centerOrigin(exitOption);
    exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
    mOptions.push_back(exitOption);

    updateOptionText();
}

void MenuState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.draw(mBackgroundSprite);

    for (const sf::Text& text : mOptions) {
        window.draw(text);
    }
}

bool MenuState::update(sf::Time) { return true; }

bool MenuState::handleEvent(const sf::Event& event) {
    if (event.type != sf::Event::KeyPressed) {
        return false;
    }

    if (event.key.code == sf::Keyboard::Return) {
        if (mOptionIndex == OptionNames::Play) {
            requestStackPop();
            requestStackPush(States::ID::Game);
        } else if (mOptionIndex == OptionNames::Exit) {
            requestStackPop();
        }

    } else if (event.key.code == sf::Keyboard::Up) {
        if (mOptionIndex > 0) {
            mOptionIndex--;
        } else {
            mOptionIndex = mOptions.size() - 1;
        }

        updateOptionText();

    } else if (event.key.code == sf::Keyboard::Down) {
        if (mOptionIndex < mOptions.size() - 1) {
            mOptionIndex++;
        } else {
            mOptionIndex = 0;
        }

        updateOptionText();
    }

    return true;
}

void MenuState::updateOptionText() {
    if (mOptions.empty()) {
        return;
    }

    for (sf::Text& text : mOptions) {
        text.setFillColor(sf::Color::White);
    }

    mOptions[mOptionIndex].setFillColor(sf::Color::Red);
}

void centerOrigin(sf::Text& text) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void centerOrigin(sf::Sprite& sprite) {
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}
