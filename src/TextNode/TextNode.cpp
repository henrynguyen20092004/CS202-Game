#include "TextNode.hpp"

#include "../Utility/Utility.hpp"

TextNode::TextNode(
    const FontHolder& FontHolder, Fonts::ID fontID, const std::string& text,
    unsigned int size
)
    : mText(text, FontHolder.get(fontID), size) {}

void TextNode::setText(const std::string& text) { mText.setString(text); }

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    target.draw(mText, states);
}
