#ifndef TEXT_NODE_HPP
#define TEXT_NODE_HPP

#include "../ResourceHolder/ResourceHolder.hpp"
#include "../SceneNode/SceneNode.hpp"

class TextNode : public SceneNode {
   public:
    typedef std::unique_ptr<TextNode> Ptr;

    TextNode(
        const FontHolder& FontHolder, Fonts::ID fontID, const std::string& text,
        unsigned int size
    );

    void setText(const std::string& text);

   private:
    sf::Text mText;

    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const override;
};

#endif
