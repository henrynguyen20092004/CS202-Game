#ifndef TEXT_NODE_HPP
#define TEXT_NODE_HPP

#include "../ResourceHolder/ResourceHolder.hpp"
#include "../SceneNode/SceneNode.hpp"

class TextNode : public SceneNode {
   public:
    typedef std::unique_ptr<TextNode> Ptr;

    TextNode(const FontHolder& fonts, const std::string& text);

    void setString(const std::string& text);

   private:
    sf::Text mText;

    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const override;
};

#endif
