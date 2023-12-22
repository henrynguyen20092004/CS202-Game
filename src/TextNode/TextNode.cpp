#include "TextNode.hpp"

#include "../Utility/Utility.hpp"

TextNode::TextNode(const FontHolder& fonts, const std::string& text)
    : mText(text, fonts.get(Fonts::ID::Dosis), 20) {
    centerOrigin(mText);
}

void TextNode::setString(const std::string& text) { mText.setString(text); }

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    target.draw(mText, states);
}
