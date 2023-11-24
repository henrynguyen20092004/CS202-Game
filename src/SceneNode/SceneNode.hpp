#ifndef SCENE_NODE_HPP
#define SCENE_NODE_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class SceneNode : public sf::Transformable,
                  public sf::Drawable,
                  private sf::NonCopyable {
   public:
    typedef std::unique_ptr<SceneNode> Ptr;

    void attachChild(Ptr child);
    Ptr detachChild(const SceneNode& node);

    sf::Vector2f getWorldPosition() const;
    sf::Transform getWorldTransform() const;

    void handleEvent(const sf::Event& event);
    void update(sf::Time deltaTime);

   private:
    std::vector<Ptr> mChildren;
    SceneNode* mParent = nullptr;

    virtual void handleEventCurrent(const sf::Event& event);
    void handleEventChildren(const sf::Event& event);

    virtual void updateCurrent(sf::Time deltaTime);
    void updateChildren(sf::Time deltaTime);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const;
    void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
