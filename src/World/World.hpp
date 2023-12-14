#ifndef WORLD_HPP
#define WORLD_HPP

#include <array>

#include "../Player/Player.hpp"
#include "../PlayerSettings/PlayerSettings.hpp"
#include "../ResourceHolder/ResourceHolder.hpp"
#include "../SceneNode/SceneNode.hpp"

class World : private sf::NonCopyable {
   public:
    World(sf::RenderWindow& window, TextureHolder& textureHolder);

    void handleEvent(const sf::Event& event);
    void update(sf::Time deltaTime);
    void draw();

   private:
    enum Layer { MapLayer, PlayerLayer, LayerCount };

    sf::RenderWindow& mWindow;
    sf::View mWorldView;
    TextureHolder& mTextureHolder;

    // TODO: Create SettingsState and move this there
    PlayerSettings mPlayerSettings;
    Player* mPlayer;

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;

    sf::FloatRect mWorldBounds;
    float mScrollSpeed = -50.f;

    void buildScene();
    void updateView();
};

#endif
