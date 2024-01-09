#ifndef WORLD_HPP
#define WORLD_HPP

#include "../Map/Map.hpp"
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
    enum Layer { MapLayer, PlayerLayer, EffectLayer, IconLayer, LayerCount };

    sf::RenderWindow& mWindow;
    TextureHolder& mTextureHolder;
    FontHolder& mFontHolder;

    sf::View mWorldView;
    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;

    int mSeasonIndex = 0;
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
