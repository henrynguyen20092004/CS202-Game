#ifndef LANE_HPP
#define LANE_HPP

#include <array>

#include "../Factory/Factory.hpp"

class Lane : public SceneNode {
   public:
    typedef std::unique_ptr<Lane> Ptr;

    Lane(TextureHolder& textureHolder, const sf::Vector2f& position);

    virtual void handlePlayerCollision(Player& player) = 0;

   protected:
    TextureHolder& mTextureHolder;

    enum Layer {
        LaneLayer,
        TileLayer,
        ObjectLayer,
        TrafficLightLayer,
        LayerCount,
    };

    std::array<SceneNode*, LayerCount> mSceneLayers;

    void buildScene(Textures::ID textureID);
};

#endif
