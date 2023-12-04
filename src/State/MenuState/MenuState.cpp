#include "MenuState.hpp"

MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context), mOptionIndex(0) {
    sf::Texture& texture = context.textures->get(Textures::ID::TitleScreen);
    sf::Font& font = context.fonts->get(Fonts::ID::Main);

    mBackgroundSprite.setTexture(texture);

    sf::Text playOption;
    playOption.setFont(font);
    playOption.setString("Play");
    // centerOrigin(playOption);
    playOption.setPosition(context.window->getView().getSize() / 2.f);
    mOptions.push_back(playOption);

    sf::Text exitOption;
    exitOption.setFont(font);
    exitOption.setString("Exit");
    // centerOrigin(exitOption);
    exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
    mOptions.push_back(exitOption);

    updateOptionText();
}

void MenuState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

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
        if (mOptionIndex == static_cast<int>(OptionNames::Play)) {
            requestStackPop();
            requestStackPush(States::ID::Game);
        } else if (mOptionIndex == static_cast<int>(OptionNames::Exit)) {
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