#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "../State/GameState/GameState.hpp"
#include "../State/MenuState/MenuState.hpp"
#include "../StateStack/StateStack.hpp"
#include "../World/World.hpp"

class Program {
   public:
    Program();
    ~Program();

    void run();

   private:
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
    sf::RenderWindow mWindow;

    World mWorld;

    void handleEvent(sf::Event &event);
    void update();
    void draw();
};

#endif
