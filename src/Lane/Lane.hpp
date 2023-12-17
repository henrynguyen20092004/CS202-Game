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
    enum Layer {
        LaneLayer,
        ObjectLayer,
        TrafficLightLayer,
        LayerCount,
    };

    TextureHolder& mTextureHolder;

    std::array<SceneNode*, LayerCount> mSceneLayers;

   protected:
    void buildScene(Textures::ID textureID);
};

#endif
