#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../../Player/Player.hpp"
#include "../../World/World.hpp"
#include "../State.hpp"

class GameState : public State {
   public:
    GameState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

   private:
    World mWorld;
    // Player& mPlayer;
};

#endif  // GAMESTATE_HPP