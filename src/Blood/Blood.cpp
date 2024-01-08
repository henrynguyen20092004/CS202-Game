#include "Blood.hpp"

Blood::Blood(Player& player) : mPlayer(player) {}

void Blood::updateCurrent(sf::Time deltaTime) {
    setPosition(-sf::Vector2f((90 - mPlayer.getSize().x) / 2, 30));
}

void Blood::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    sf::RectangleShape frame(sf::Vector2f(90, 10));
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineColor(sf::Color::Black);
    frame.setOutlineThickness(2);

    sf::RectangleShape blood(sf::Vector2f(
        (float)mPlayer.getHealth() / mPlayer.getMaxHealth() * 90, 10.f
    ));
    blood.setFillColor(sf::Color::Red);

    if (mPlayer.isImmortal()) {
        frame.setFillColor(sf::Color(
            frame.getFillColor().a, frame.getFillColor().g,
            frame.getFillColor().b, 127
        ));
        blood.setFillColor(sf::Color(
            blood.getFillColor().r, blood.getFillColor().g,
            blood.getFillColor().b, 127
        ));
    }

    target.draw(frame, states);
    target.draw(blood, states);
}
