#ifndef BLOOD_HPP
#define BLOOD_HPP

#include "../Player/Player.hpp"

class Blood : public SceneNode {
   public:
    typedef std::unique_ptr<Blood> Ptr;

    Blood(Player& player);

   private:
    Player& mPlayer;

    void updateCurrent(sf::Time deltaTime) override;
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const override;
};

#endif
