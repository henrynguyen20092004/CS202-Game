#ifndef REGENERATE_HPP
#define REGENERATE_HPP

#include "../PowerUp.hpp"

class Regenerate : public PowerUp {
   public:
    Regenerate(const PowerUpIconArgs& powerUpIconArgs, Player& player);

   private:
    void activate() override;
    void deactivate() override;
};

#endif
