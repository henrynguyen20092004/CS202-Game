#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <SFML/Graphics.hpp>

class Program {
   private:
    sf::RenderWindow mWindow;

    void handleEvent();

   public:
    Program();
    ~Program();
    void run();
};

#endif
