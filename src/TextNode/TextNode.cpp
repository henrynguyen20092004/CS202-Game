#include "TextNode.hpp"

#include "../Utility/Utility.hpp"

TextNode::TextNode(const FontHolder& fontHolder, const std::string& text, int size)
    : mText(text, fontHolder.get(Fonts::ID::Dosis), size) {
    centerOrigin(mText);
}

void TextNode::setString(const std::string& text) { mText.setString(text); }

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    target.draw(mText, states);
}
