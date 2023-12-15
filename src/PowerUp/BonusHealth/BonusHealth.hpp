#ifndef BONUS_HEALTH_HPP
#define BONUS_HEALTH_HPP

#include "../PowerUp.hpp"

class BonusHealth : public PowerUp {
   public:
    BonusHealth(Player& player);

   private:
    void activate() override;
};

#endif
