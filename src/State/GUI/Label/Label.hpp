#ifndef LABEL_HPP
#define LABEL_HPP

#include "../../../ResourceHolder/ResourceHolder.hpp"
#include "../Component/Component.hpp"

namespace GUI {
class Label : public Component {
   public:
    typedef std::shared_ptr<Label> Ptr;

    Label(const std::string& text, const FontHolder& fonts);
    bool isSelectable() const override;
    void setText(const std::string& text);
    void handleEvent(const sf::Event& event) override;
    void setTextColor(const sf::Color& color);

   private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Text mText;
};
}  // namespace GUI

#endif
