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

    addDirButtonLabel(
        Directions::ID::Left, sf::Vector2f(-250.f, 300.f), "Move Left", context
    );
    addDirButtonLabel(
        Directions::ID::Right, sf::Vector2f(-250.f, 350.f), "Move Right",
        context
    );
    addDirButtonLabel(
        Directions::ID::Up, sf::Vector2f(-250.f, 400.f), "Move Up", context
    );
    addDirButtonLabel(
        Directions::ID::Down, sf::Vector2f(-250.f, 450.f), "Move Down", context
    );

    addPowButtonLabel(
        PowerUp::Type::Immortality, sf::Vector2f(250.f, 300.f), "Immortality",
        context
    );
    addPowButtonLabel(
        PowerUp::Type::SlowTime, sf::Vector2f(250.f, 350.f), "Slow Time",
        context
    );

    updateLabels();

    auto resetButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Reset"
    );
    resetButton->setPosition(windowSize.x / 2, 600.f);
    resetButton->setCallback([this]() {
        getContext().playerSettings->setToDefault();
        getContext().powerUpSettings->setToDefault();
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
    int ActionCount = static_cast<int>(PowerUp::Type::TypeButtonCount) +
                      static_cast<int>(Directions::ID::DirectionCount);
    for (std::size_t action = 0; action < ActionCount; ++action) {
        if (mBindingButtons[action]->isActive()) {
            isKeyBinding = true;
            if (event.type == sf::Event::KeyReleased &&
                action >= static_cast<int>(Directions::ID::DirectionCount)) {
                getContext().powerUpSettings->assignKey(
                    event.key.code,
                    static_cast<PowerUp::Type>(
                        action -
                        static_cast<int>(Directions::ID::DirectionCount)
                    )
                );
                mBindingButtons[action]->deactivate();
            } else if (event.type == sf::Event::KeyReleased) {
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
        mGUIContainer.handleEvent(event, *getContext().window);

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
    for (std::size_t i = 0;
         i < static_cast<int>(PowerUp::Type::TypeButtonCount); ++i) {
        sf::Keyboard::Key key = getContext().powerUpSettings->getAssignedKey(
            static_cast<PowerUp::Type>(i)
        );
        mBindingLabels[i + static_cast<int>(Directions::ID::DirectionCount)]
            ->setText(toString(key));
        mBindingLabels[i + static_cast<int>(Directions::ID::DirectionCount)]
            ->setTextColor(sf::Color(0, 255, 255));
    }
}

void SettingsState::addDirButtonLabel(
    Directions::ID direction, const sf::Vector2f& position,
    const std::string& text, Context context
) {
    int index = static_cast<int>(direction);

    mBindingButtons[index] = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, text
    );

    sf::Vector2f windowSize(context.window->getSize());

    mBindingButtons[index]->setPosition(
        windowSize.x / 2.f + position.x, position.y
    );
    mBindingButtons[index]->setToggle(true);

    mBindingLabels[index] =
        std::make_shared<GUI::Label>("", *context.fontHolder);
    mBindingLabels[index]->setPosition(
        windowSize.x / 2.f + position.x + 120.f, position.y
    );

    mGUIContainer.addComponent(mBindingButtons[index]);
    mGUIContainer.addComponent(mBindingLabels[index]);
}

void SettingsState::addPowButtonLabel(
    PowerUp::Type power, const sf::Vector2f& position, const std::string& text,
    Context context
) {
    int index = static_cast<int>(Directions::ID::DirectionCount) +
                static_cast<int>(power);

    mBindingButtons[index] = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, text
    );

    sf::Vector2f windowSize(context.window->getSize());

    mBindingButtons[index]->setPosition(
        windowSize.x / 2.f + position.x, position.y
    );
    mBindingButtons[index]->setToggle(true);

    mBindingLabels[index] =
        std::make_shared<GUI::Label>("", *context.fontHolder);
    mBindingLabels[index]->setPosition(
        windowSize.x / 2.f + position.x + 120.f, position.y
    );

    mGUIContainer.addComponent(mBindingButtons[index]);
    mGUIContainer.addComponent(mBindingLabels[index]);
}
