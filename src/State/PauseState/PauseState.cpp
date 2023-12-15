#include "PauseState.hpp"

#include "../GUI/Button/Button.hpp"

PauseState::PauseState(StateStack& stack, Context context)
    : State(stack, context) {
    sf::Font& font = context.fontHolder->get(Fonts::ID::Dosis);
    sf::Vector2f viewSize = context.window->getView().getSize();

    mPausedText.setFont(font);
    mPausedText.setString("Game Paused");
    mPausedText.setCharacterSize(70);
    centerOrigin(mPausedText);
    mPausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y - 50.f);

    auto returnButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Return"
    );
    returnButton->setPosition(0.5f * viewSize.x, 0.4f * viewSize.y + 75.f);
    returnButton->setCallback([this]() { requestStackPop(); });

    auto backToMenuButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Back to menu"
    );
    backToMenuButton->setPosition(0.5f * viewSize.x, 0.4f * viewSize.y + 135.f);
    backToMenuButton->setCallback([this]() {
        requestStateClear();
        requestStackPush(States::ID::Menu);
    });
    mGUIContainer.addComponent(returnButton);
    mGUIContainer.addComponent(backToMenuButton);
}

void PauseState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize());

    window.draw(backgroundShape);
    window.draw(mPausedText);
    window.draw(mGUIContainer);
}

bool PauseState::update(sf::Time) { return false; }

bool PauseState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);

    return false;
}
