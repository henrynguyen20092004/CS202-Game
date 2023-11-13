#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <SFML/Graphics.hpp>

class Program {
   public:
    Program();
    ~Program();

    void run();

   private:
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
    sf::RenderWindow mWindow;

    void processEvents(sf::Event &event);
    void update();
    void render();
};

#endif
