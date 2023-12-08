#ifndef WORLD_HPP
#define WORLD_HPP

#include <array>

#include "../ResourceHolder/ResourceHolder.hpp"
#include "../SceneNode/SceneNode.hpp"

class World : private sf::NonCopyable {
   public:
    World(sf::RenderWindow& window, TextureHolder& textures);

    void handleEvent(const sf::Event& event);
    void update(sf::Time deltaTime);
    void draw();

   private:
    enum Layer { MapLayer, PlayerLayer, LayerCount };

    sf::RenderWindow& mWindow;
    sf::View mWorldView;
    TextureHolder& mTextureHolder;

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;

    sf::FloatRect mWorldBounds;
    float mScrollSpeed = -50.f;

    void buildScene();
};

#endif
