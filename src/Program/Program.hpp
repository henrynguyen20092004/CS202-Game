#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <SFML/Graphics.hpp>

class Program {
   public:
    Program();
    ~Program();
    void run();

   private:
    sf::RenderWindow mWindow;

    void handleEvent();
};

#endif
