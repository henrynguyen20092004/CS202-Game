#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "../../World/World.hpp"

class GameState : public State {
   public:
    GameState(StateStack& stack, Context context);

    bool handleEvent(const sf::Event& event) override;
    bool update(sf::Time deltaTime) override;
    void draw() override;

   private:
    World mWorld;
};

#endif
