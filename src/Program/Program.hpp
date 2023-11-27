#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "../State/MenuState/MenuState.hpp"
#include "../StateStack/StateStack.hpp"

class Program {
   public:
    Program();
    ~Program();

    void run();

   private:
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

    sf::RenderWindow mWindow;
    TextureHolder mTextures;
    FontHolder mFonts;

    StateStack mStateStack;

    TextureHolder mTextures;
    FontHolder mFonts;

    void loadTextures();
    void loadFonts();
    void registerState();

    StateStack mStateStack;

    void handleEvent(sf::Event &event);
    void update();
    void draw();
    void registerState();
};

#endif
