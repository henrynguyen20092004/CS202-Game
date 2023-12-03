#ifndef LANE_HPP
#define LANE_HPP

#include <array>

#include "../Factory/Factory.hpp"
#include "../SpriteNode/SpriteNode.hpp"

class Lane : public SceneNode {
   public:
    typedef std::unique_ptr<Lane> Ptr;

    Lane(TextureHolder& textureHolder, const sf::Vector2f& position);

   protected:
    enum Layer { Ground, Object, LayerCount };

    TextureHolder& mTextureHolder;

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;

    Factory* mFactory;

    virtual void buildScene() = 0;

   private:
    void updateCurrent(sf::Time deltaTime) override;
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const override;
};

#endif
