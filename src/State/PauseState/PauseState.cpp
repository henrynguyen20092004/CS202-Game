#include "PauseState.hpp"

#include "../../Utility/Utility.hpp"
#include "../GUI/Button/Button.hpp"

PauseState::PauseState(StateStack& stack, Context context)
    : State(stack, context),
      mPausedText(
          "Game Paused", context.fontHolder->get(Fonts::ID::Dosis), 70
      ) {
    sf::Vector2f windowSize(context.window->getSize());

    centerOrigin(mPausedText);
    mPausedText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 120.f);

    auto returnButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Return"
    );
    returnButton->setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
    returnButton->setCallback([this]() { requestStackPop(); });

    auto backToMenuButton = std::make_shared<GUI::Button>(
        *context.fontHolder, *context.textureHolder, "Back to menu"
    );
    backToMenuButton->setPosition(
        windowSize.x / 2.f, windowSize.y / 2.f + 60.f
    );
    backToMenuButton->setCallback([this]() {
        requestStateClear();
        requestStackPush(States::ID::Menu);
    });

    mGUIContainer.addComponent(returnButton);
    mGUIContainer.addComponent(backToMenuButton);
}

bool PauseState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event, *getContext().window);
    
    return false;
}

bool PauseState::update(sf::Time deltaTime) { return false; }

void PauseState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape(sf::Vector2f(window.getSize()));
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));

    window.draw(backgroundShape);
    window.draw(mPausedText);
    window.draw(mGUIContainer);
}
