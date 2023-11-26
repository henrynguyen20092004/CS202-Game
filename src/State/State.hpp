#ifndef STATE_HPP
#define STATE_HPP

#include <functional>
#include <vector>

#include "../Identifier/Identifier.hpp"
#include "../ResourceHolder/ResourceHolder.hpp"

class StateStack;

class State {
   public:
    typedef std::unique_ptr<State> Ptr;

    struct Context {
        Context(
            sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts
        );

        sf::RenderWindow* window;
        TextureHolder* textures;
        FontHolder* fonts;
        // Player* player;
    };

    State(StateStack& stack, Context context);
    virtual ~State();
    virtual void draw() = 0;
    virtual bool update(sf::Time dt) = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;

   protected:
    void requestStackPush(States::ID stateID);
    void requestStackPop();
    void requestStateClear();
    Context getContext() const;

   private:
    StateStack* mStack;
    Context mContext;
};

#endif
