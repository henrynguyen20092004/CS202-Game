#ifndef WORLD_HPP
#define WORLD_HPP

#include <array>

#include "../Map/Map.hpp"
#include "../PowerUpList/PowerUpList.hpp"
#include "../State/State.hpp"

class World : private sf::NonCopyable {
   public:
    World(const State::Context& context, bool isMultiplayer = false);

    void handleEvent(const sf::Event& event);
    void update(sf::Time deltaTime);
    void draw();

    bool isPlayerAlive() const;

   private:
    enum Layer { MapLayer, PlayerLayer, IconLayer, LayerCount };

    sf::RenderWindow& mWindow;
    TextureHolder& mTextureHolder;
    FontHolder& mFontHolder;

    sf::View mWorldView;
    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;

    Map* mMap;
    std::vector<Player*> mPlayers;

    const float mScrollSpeed = -50.f;

    void buildScene(const State::Context& context);
    void updateView();
};

#endif
