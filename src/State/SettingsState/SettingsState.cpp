#include "SettingsState.hpp"

SettingsState::SettingsState(StateStack& stack, Context context)
    : State(stack, context) {
    sf::Texture& backgroundTexture =
        context.textureHolder->get(Textures::ID::MenuBackground);
    sf::Vector2f windowSize(context.window->getSize());

    mBackgroundSprite.setTexture(backgroundTexture);
    mBackgroundSprite.setScale(
        windowSize.x / backgroundTexture.getSize().x,
        windowSize.y / backgroundTexture.getSize().y
    );
    for (int player = 1; player <= 2; ++player) {
        addDirectionButtonLabel(
            Directions::ID::Left, player, sf::Vector2f(-250.f, 200.f),
            "Move Left", context
        );
        addDirectionButtonLabel(
            Directions::ID::Right, player, sf::Vector2f(-250.f, 250.f),
            "Move Right", context
        );
        addDirectionButtonLabel(
            Directions::ID::Up, player, sf::Vector2f(-250.f, 300.f), "Move Up",
            context
        );
        addDirectionButtonLabel(
            Directions::ID::Down, player, sf::Vector2f(-250.f, 350.f),
            "Move Down", context
        );

        addPowerButtonLabel(
            PowerUp::Type::Immortality, player, sf::Vector2f(-250.f, 400.f),
            "Immortality", context
        );
        addPowerButtonLabel(
            PowerUp::Type::SlowTime, player, sf::Vector2f(-250.f, 450.f),
            "Slow Time", context
        );
    }

    updateLabels();

    auto resetButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Reset"
    );
    resetButton->setPosition(windowSize.x / 2, 600.f);
    resetButton->setCallback([this]() {
        getContext().playerSettings1->setToDefault();
        getContext().powerUpSettings1->setToDefault();
        getContext().playerSettings2->setToDefault(true);
        getContext().powerUpSettings2->setToDefault(true);
        updateLabels();
    });

    auto backButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Back"
    );
    backButton->setPosition(windowSize.x / 2.f, 700.f);
    backButton->setCallback([this]() { requestStackPop(); });

    mGUIContainer.addComponent(resetButton);
    mGUIContainer.addComponent(backButton);
}

bool SettingsState::handleEvent(const sf::Event& event) {
    bool isKeyBinding = false;
    int directionCount = static_cast<int>(Directions::ID::DirectionCount);
    int actionCount = directionCount + PowerUp::Type::TypeButtonCount;

    for (size_t buttonIndex = 0; buttonIndex < mBindingButtons.size();
         ++buttonIndex) {
        if (mBindingButtons[buttonIndex]->isActive()) {
            isKeyBinding = true;

            if (buttonIndex < actionCount &&
                event.type == sf::Event::KeyReleased) {
                if (buttonIndex >= directionCount) {
                    getContext().powerUpSettings1->assignKey(
                        event.key.code,
                        static_cast<PowerUp::Type>(buttonIndex - directionCount)
                    );
                } else {
                    getContext().playerSettings1->assignKey(
                        event.key.code, static_cast<Directions::ID>(buttonIndex)
                    );
                }

                mBindingButtons[buttonIndex]->deactivate();
            } else if (event.type == sf::Event::KeyReleased) {
                if (buttonIndex >= directionCount + actionCount) {
                    getContext().powerUpSettings2->assignKey(
                        event.key.code,
                        static_cast<PowerUp::Type>(
                            buttonIndex - directionCount - actionCount
                        )
                    );
                } else {
                    getContext().playerSettings2->assignKey(
                        event.key.code,
                        static_cast<Directions::ID>(buttonIndex - actionCount)
                    );
                }

                mBindingButtons[buttonIndex]->deactivate();
            }

            break;
        }
    }

    if (isKeyBinding) {
        updateLabels();
    } else {
        mGUIContainer.handleEvent(event, *getContext().window);
    }

    return false;
}

bool SettingsState::update(sf::Time deltaTime) { return true; }

void SettingsState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.draw(mBackgroundSprite);
    window.draw(mGUIContainer);
}

void SettingsState::updateLabels() {
    sf::Keyboard::Key key1;
    sf::Keyboard::Key key2;
    int directionCount = static_cast<int>(Directions::ID::DirectionCount);
    int actionCount = directionCount + PowerUp::Type::TypeButtonCount;

    for (int i = 0; i < actionCount; ++i) {
        if (i < directionCount) {
            key1 = getContext().playerSettings1->getAssignedKey(
                static_cast<Directions::ID>(i)
            );
            key2 = getContext().playerSettings2->getAssignedKey(
                static_cast<Directions::ID>(i)
            );
        } else {
            key1 = getContext().powerUpSettings1->getAssignedKey(
                static_cast<PowerUp::Type>(i - directionCount)
            );
            key2 = getContext().powerUpSettings2->getAssignedKey(
                static_cast<PowerUp::Type>(i - directionCount)
            );
        }

        mBindingLabels[i]->setText(toString(key1));
        mBindingLabels[i]->setTextColor(sf::Color(0, 255, 255));
        mBindingLabels[i + actionCount]->setText(toString(key2));
        mBindingLabels[i + actionCount]->setTextColor(sf::Color(0, 255, 255));
    }
}

void SettingsState::addDirectionButtonLabel(
    Directions::ID direction, int player, sf::Vector2f position,
    const std::string& text, Context context
) {
    int index = static_cast<int>(direction);

    if (player == 2) {
        position.x = -position.x;
        index +=
            (static_cast<int>(Directions::ID::DirectionCount) +
             PowerUp::Type::TypeButtonCount);
    }

    sf::Vector2f windowSize(context.window->getSize());

    mBindingButtons[index] = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, text
    );
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

void SettingsState::addPowerButtonLabel(
    PowerUp::Type power, int player, sf::Vector2f position,
    const std::string& text, Context context
) {
    int index = static_cast<int>(Directions::ID::DirectionCount) + power;

    if (player == 2) {
        position.x = -position.x;
        index +=
            (static_cast<int>(Directions::ID::DirectionCount) +
             PowerUp::Type::TypeButtonCount);
    }

    sf::Vector2f windowSize(context.window->getSize());

    mBindingButtons[index] = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, text
    );
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
