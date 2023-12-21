#include "SettingsState.hpp"

#include <iostream>
using namespace std;

SettingsState::SettingsState(StateStack& stack, Context context)
    : State(stack, context), mPlayerSettings(*context.playerSettings) {
    sf::Texture& backgroundTexture =
        context.textureHolder->get(Textures::ID::MenuBackground);
    sf::Vector2f windowSize(context.window->getSize());

    mBackgroundSprite.setTexture(backgroundTexture);
    mBackgroundSprite.setScale(
        windowSize.x / backgroundTexture.getSize().x,
        windowSize.y / backgroundTexture.getSize().y
    );

    addButtonLabel(Directions::ID::Left, 300.f, "Move Left", context);
    addButtonLabel(Directions::ID::Right, 350.f, "Move Right", context);
    addButtonLabel(Directions::ID::Up, 400.f, "Move Up", context);
    addButtonLabel(Directions::ID::Down, 450.f, "Move Down", context);

    updateLabels();

    auto resetButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Reset"
    );
    resetButton->setPosition(windowSize.x / 2, 600.f);
    resetButton->setCallback([this]() {
        getContext().playerSettings->setToDefault();
        updateLabels();
    });

    mGUIContainer.addComponent(resetButton);

    auto backButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Back"
    );
    backButton->setPosition(windowSize.x / 2.f, 700.f);
    backButton->setCallback([this]() { requestStackPop(); });

    mGUIContainer.addComponent(backButton);
}

void SettingsState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.draw(mBackgroundSprite);
    window.draw(mGUIContainer);
}

bool SettingsState::update(sf::Time deltaTime) { return true; }

bool SettingsState::handleEvent(const sf::Event& event) {
    bool isKeyBinding = false;
    for (std::size_t action = 0;
         action < static_cast<int>(Directions::ID::DirectionCount); ++action) {
        if (mBindingButtons[action]->isActive()) {
            isKeyBinding = true;
            if (event.type == sf::Event::KeyReleased) {
                getContext().playerSettings->assignKey(
                    event.key.code, static_cast<Directions::ID>(action)
                );
                mBindingButtons[action]->deactivate();
            }
            break;
        }
    }

    if (isKeyBinding)
        updateLabels();
    else
        mGUIContainer.handleEvent(event);

    return false;
}

void SettingsState::updateLabels() {
    for (std::size_t i = 0;
         i < static_cast<int>(Directions::ID::DirectionCount); ++i) {
        sf::Keyboard::Key key = getContext().playerSettings->getAssignedKey(
            static_cast<Directions::ID>(i)
        );
        mBindingLabels[i]->setText(toString(key));
        mBindingLabels[i]->setTextColor(sf::Color(0, 255, 255));
    }
}

void SettingsState::addButtonLabel(
    Directions::ID direction, float y, const std::string& text, Context context
) {
    mBindingButtons[static_cast<int>(direction)] =
        std::make_shared<GUI::Button>(
            *context.fontHolder, *context.textureHolder, text
        );

    sf::Vector2f windowSize(context.window->getSize());

    mBindingButtons[static_cast<int>(direction)]->setPosition(
        windowSize.x / 2.f, y
    );
    mBindingButtons[static_cast<int>(direction)]->setToggle(true);

    mBindingLabels[static_cast<int>(direction)] =
        std::make_shared<GUI::Label>("", *context.fontHolder);
    mBindingLabels[static_cast<int>(direction)]->setPosition(
        windowSize.x / 2.f + 120.f, y
    );

    mGUIContainer.addComponent(mBindingButtons[static_cast<int>(direction)]);
    mGUIContainer.addComponent(mBindingLabels[static_cast<int>(direction)]);
}
