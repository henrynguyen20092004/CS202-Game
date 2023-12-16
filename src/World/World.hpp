#ifndef WORLD_HPP
#define WORLD_HPP

#include <array>

#include "../Player/Player.hpp"
#include "../PlayerSettings/PlayerSettings.hpp"
#include "../PowerUpList/PowerUpList.hpp"

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

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;

    // TODO: Create SettingsState and move these there
    PlayerSettings mPlayerSettings;
    PowerUpSettings mPowerUpSettings;

    Player* mPlayer;
    PowerUpList* mPowerUpList;

    sf::FloatRect mWorldBounds;
    float mScrollSpeed = -50.f;

    void buildScene();
    void updateView();
    void handleCollision();
};

#endif
