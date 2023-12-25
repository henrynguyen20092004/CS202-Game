#include "Button.hpp"

#include "../../../Utility/Utility.hpp"

namespace GUI {

Button::Button(
    const FontHolder& fontHolder, const TextureHolder& textureHolder,
    const std::string& text
)
    : mNormalTexture(textureHolder.get(Textures::ID::ButtonNormal)),
      mSelectedTexture(textureHolder.get(Textures::ID::ButtonSelected)),
      mPressedTexture(textureHolder.get(Textures::ID::ButtonPressed)),
      mText(text, fontHolder.get(Fonts::ID::Dosis), 20),
      mIsToggle(false) {
    mSprite.setTexture(mNormalTexture);
    centerOrigin(mSprite);
    centerOrigin(mText);
}

void Button::setCallback(const Callback& callback) {
    mCallback = std::move(callback);
}

void Button::setText(const std::string& text) {
    mText.setString(text);
    centerOrigin(mText);
}

void Button::setToggle(bool flag) { mIsToggle = flag; }

bool Button::isSelectable() const { return true; }

void Button::select() {
    Component::select();
    mSprite.setTexture(mSelectedTexture);
}

void Button::deselect() {
    Component::deselect();
    mSprite.setTexture(mNormalTexture);
}

void Button::activate() {
    Component::activate();

    if (mIsToggle)
        mSprite.setTexture(mPressedTexture);
    else
        deactivate();

    if (mCallback) mCallback();
}

void Button::deactivate() {
    Component::deactivate();

    if (mIsToggle) {
        mSprite.setTexture(isSelected() ? mSelectedTexture : mNormalTexture);
    }
}

void Button::handleMouseEvent(
    const sf::Event& event, const sf::RenderWindow& window
) {}

void Button::handleEvent(
    const sf::Event& event, const sf::RenderWindow& window
) {}

sf::FloatRect Button::getGlobalBounds() const {
    return getTransform().transformRect(mSprite.getGlobalBounds());
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mSprite, states);
    target.draw(mText, states);
}

}  // namespace GUI
