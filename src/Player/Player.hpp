#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <functional>

#include "../ResourceHolder/ResourceHolder.hpp"
#include "../SpriteNode/SpriteNode.hpp"

class Player : public SpriteNode {
   public:
    typedef std::unique_ptr<Player> Ptr;

    enum Action {
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown,
        ActionCount,
    };

    Player(TextureHolder& mTextureHolder, sf::View& worldView);

    void updateCurrent(sf::Time deltaTime) override;

    void assignKey(sf::Keyboard::Key key, Action action);
    sf::Keyboard::Key getAssignedKey(Action action) const;

   private:
    std::map<sf::Keyboard::Key, Action> mKeyBinding;
    std::map<Action, std::function<void(Player&)>> mActionBinding;

    sf::View& mWorldView;

    void handleEventCurrent(const sf::Event& event) override;

    void initializePosition(const sf::Vector2f& viewCenter);
    void initializeKeyBinding();
    void initializeActionBinding();

    bool isOutOfBounds();

    void die();
};

#endif
