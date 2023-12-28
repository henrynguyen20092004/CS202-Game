#ifndef WORLD_HPP
#define WORLD_HPP

#include <array>

#include "../Map/Map.hpp"
#include "../Player/Player.hpp"
#include "../PowerUpList/PowerUpList.hpp"

class World : private sf::NonCopyable {
   public:
    World(
        sf::RenderWindow& window, TextureHolder& textureHolder,
        FontHolder& fontHolder
    );

    void handleEvent(const sf::Event& event);
    void update(sf::Time deltaTime);
    void draw();

    bool isPlayerAlive() const;

   private:
    enum Layer { MapLayer, PlayerLayer, IconLayer, LayerCount };

    sf::RenderWindow& mWindow;
    sf::View mWorldView;
    TextureHolder& mTextureHolder;
    FontHolder& mFontHolder;

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;

    // TODO: Create SettingsState and move these there
    PlayerSettings mPlayerSettings;
    PowerUpSettings mPowerUpSettings;

    Map* mMap;
    Player* mPlayer;
    PowerUpList* mPowerUpList;

    float mScrollSpeed = -50.f;

    void buildScene();
    void updateView();
    void handlePlayerCollision();
};

#endif
