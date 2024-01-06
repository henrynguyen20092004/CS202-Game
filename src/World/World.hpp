#ifndef WORLD_HPP
#define WORLD_HPP

#include <array>

#include "../Map/Map.hpp"
#include "../PowerUpList/PowerUpList.hpp"
#include "../State/State.hpp"

class Score;

class World : private sf::NonCopyable {
   public:
    World(const State::Context& context, bool isMultiplayer, bool isLoading);
    ~World();

    void handleEvent(const sf::Event& event);
    void update(sf::Time deltaTime);
    void draw();

    int getDeadPlayer() const;

   private:
    enum Layer { MapLayer, PlayerLayer, IconLayer, LayerCount };

    sf::RenderWindow& mWindow;
    TextureHolder& mTextureHolder;
    FontHolder& mFontHolder;

    sf::View mWorldView;
    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;

    std::vector<Player*> mPlayers;
    std::vector<PowerUpList*> mPowerUpLists;
    Score* mScore = nullptr;
    Map* mMap;

    const float mScrollSpeed = -50.f;

    void buildScene(const State::Context& context, bool isLoading);
    void updateView();

    void saveWorld();
    void loadWorld();

    void savePlayerTexture() const;
    void loadPlayerTexture();
};

#endif
