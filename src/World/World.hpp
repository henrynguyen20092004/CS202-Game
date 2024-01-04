#ifndef WORLD_HPP
#define WORLD_HPP

#include <array>

#include "../Map/Map.hpp"
#include "../PowerUpList/PowerUpList.hpp"
#include "../State/State.hpp"

class World : private sf::NonCopyable {
   public:
    World(State::Context context);

    void handleEvent(const sf::Event& event);
    void update(sf::Time deltaTime);
    void draw();

    bool isPlayerAlive() const;

   private:
    enum Layer { MapLayer, PlayerLayer, IconLayer, LayerCount };

    sf::RenderWindow& mWindow;
    TextureHolder& mTextureHolder;
    FontHolder& mFontHolder;
    PlayerSettings& mPlayerSettings;
    PowerUpSettings& mPowerUpSettings;

    sf::View mWorldView;
    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;

    Player* mPlayer;
    Map* mMap;
    PowerUpList* mPowerUpList;

    const float mScrollSpeed = -50.f;

    void buildScene();
    void updateView();
};

#endif
