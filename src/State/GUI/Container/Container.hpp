#ifndef GUI_CONTAINER_HPP
#define GUI_CONTAINER_HPP

#include <vector>

#include "../Component/Component.hpp"

namespace GUI {

class Container : public Component {
   public:
    typedef std::shared_ptr<Container> Ptr;

    Container();

    void addComponent(Component::Ptr component);

    bool isSelectable() const override;
    void handleMouseEvent(
        const sf::Event& event, const sf::RenderWindow& window
    ) override;
    void handleEvent(
        const sf::Event& event, const sf::RenderWindow& window
    ) override;

   private:
    std::vector<Component::Ptr> mChildren;
    int mSelectedChild;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    bool hasSelection() const;
    void select(int index);
    void selectNext();
    void selectPrevious();
};

}  // namespace GUI

#endif
