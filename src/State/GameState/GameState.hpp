#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "../../World/World.hpp"
#include "../State.hpp"

class GameState : public State {
   public:
    GameState(StateStack& stack, Context context);

    void draw() override;
    bool update(sf::Time deltaTime) override;
    bool handleEvent(const sf::Event& event) override;

   private:
    World mWorld;
};

#endif
