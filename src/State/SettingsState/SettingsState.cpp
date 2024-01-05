#include "SettingsState.hpp"

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

    addDirectionButtonLabel(
        Directions::ID::Left, sf::Vector2f(-250.f, 300.f), "Move Left", context
    );
    addDirectionButtonLabel(
        Directions::ID::Right, sf::Vector2f(-250.f, 350.f), "Move Right",
        context
    );
    addDirectionButtonLabel(
        Directions::ID::Up, sf::Vector2f(-250.f, 400.f), "Move Up", context
    );
    addDirectionButtonLabel(
        Directions::ID::Down, sf::Vector2f(-250.f, 450.f), "Move Down", context
    );

    addPowerButtonLabel(
        PowerUp::Type::Immortality, sf::Vector2f(250.f, 300.f), "Immortality",
        context
    );
    addPowerButtonLabel(
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

    for (std::size_t action = 0; action < mBindingButtons.size(); ++action) {
        if (mBindingButtons[action]->isActive()) {
            isKeyBinding = true;

            if (event.type == sf::Event::KeyReleased) {
                if (action >= directionCount) {
                    getContext().powerUpSettings->assignKey(
                        event.key.code,
                        static_cast<PowerUp::Type>(action - directionCount)
                    );
                } else {
                    getContext().playerSettings->assignKey(
                        event.key.code, static_cast<Directions::ID>(action)
                    );
                }

                mBindingButtons[action]->deactivate();
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
    sf::Keyboard::Key key;
    int directionCount = static_cast<int>(Directions::ID::DirectionCount);

    for (int i = 0; i < mBindingLabels.size(); ++i) {
        if (i < directionCount) {
            key = getContext().playerSettings->getAssignedKey(
                static_cast<Directions::ID>(i)
            );
        } else {
            key = getContext().powerUpSettings->getAssignedKey(
                static_cast<PowerUp::Type>(i - directionCount)
            );
        }

        mBindingLabels[i]->setText(toString(key));
        mBindingLabels[i]->setTextColor(sf::Color(0, 255, 255));
    }
}

void SettingsState::addDirectionButtonLabel(
    Directions::ID direction, const sf::Vector2f& position,
    const std::string& text, Context context
) {
    int index = static_cast<int>(direction);
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
    PowerUp::Type power, const sf::Vector2f& position, const std::string& text,
    Context context
) {
    int index = static_cast<int>(Directions::ID::DirectionCount) +
                static_cast<int>(power);
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
