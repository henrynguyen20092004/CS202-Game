#ifndef WORLD_HPP
#define WORLD_HPP

#include <array>

#include "../Map/Map.hpp"
#include "../PowerUpList/PowerUpList.hpp"
#include "../State/State.hpp"

class World : private sf::NonCopyable {
   public:
<<<<<<< HEAD
    World(
        sf::RenderWindow& window, TextureHolder& textureHolder,
        FontHolder& fontHolder
    );
=======
    World(State::Context context);
>>>>>>> a7f2657 (Add SettingState)

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

    PlayerSettings& mPlayerSettings;
    PowerUpSettings& mPowerUpSettings;

    Map* mMap;
    Player* mPlayer;
    PowerUpList* mPowerUpList;

    float mScrollSpeed = -50.f;

    void buildScene();
    void updateView();
    void handlePlayerCollision();
};

#endif
