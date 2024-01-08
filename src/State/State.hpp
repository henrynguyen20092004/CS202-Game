#ifndef STATE_HPP
#define STATE_HPP

#include "../HighScore/HighScore.hpp"
#include "../PlayerSettings/PlayerSettings.hpp"
#include "../PowerUpSettings/PowerUpSettings.hpp"
#include "../ResourceHolder/ResourceHolder.hpp"

class StateStack;

class State {
   public:
    typedef std::unique_ptr<State> Ptr;

    struct Context {
        Context(
            sf::RenderWindow& window, TextureHolder& textureHolder,
            FontHolder& fontHolder, PlayerSettings& playerSettings1,
            PlayerSettings& playerSettings2, PowerUpSettings& powerUpSettings1,
            PowerUpSettings& powerUpSettings2, HighScore& highScore
        );

        sf::RenderWindow* window;
        TextureHolder* textureHolder;
        FontHolder* fontHolder;

        PlayerSettings* playerSettings1;
        PlayerSettings* playerSettings2;
        PowerUpSettings* powerUpSettings1;
        PowerUpSettings* powerUpSettings2;

        HighScore* mHighScore;
    };

    State(StateStack& stack, Context context);
    virtual ~State();

    virtual bool handleEvent(const sf::Event& event) = 0;
    virtual bool update(sf::Time deltaTime) = 0;
    virtual void draw() = 0;

   protected:
    void requestStackPush(States::ID stateID);
    void requestStackPop();
    void requestStackClear();
    Context getContext() const;

   private:
    StateStack* mStack;
    Context mContext;
};

#endif
