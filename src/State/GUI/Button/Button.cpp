#include "Button.hpp"

#include "../../../Utility/Utility.hpp"

namespace GUI {

Button::Button(
    const FontHolder& fonts, const TextureHolder& textures,
    const std::string& text
)
    : mNormalTexture(textures.get(Textures::ID::ButtonNormal)),
      mSelectedTexture(textures.get(Textures::ID::ButtonSelected)),
      mPressedTexture(textures.get(Textures::ID::ButtonPressed)),
      mText(text, fonts.get(Fonts::ID::Dosis), 20),
      mIsToggle(false) {
    mSprite.setTexture(mNormalTexture);
    centerOrigin(mSprite);
    centerOrigin(mText);
}

void Button::setCallback(const Callback& callback) {
    mCallback = std::move(callback);
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
    mCallback();

    if (mIsToggle) {
        mSprite.setTexture(mPressedTexture);
    } else {
        deactivate();
    }
}

void Button::deactivate() {
    Component::deactivate();

    if (mIsToggle) {
        mSprite.setTexture(isSelected() ? mSelectedTexture : mNormalTexture);
    }
}

void Button::handleEvent(const sf::Event&) {}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mSprite, states);
    target.draw(mText, states);
}

}  // namespace GUI
