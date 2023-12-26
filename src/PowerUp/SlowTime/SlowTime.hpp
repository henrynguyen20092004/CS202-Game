#ifndef SLOW_TIME_HPP
#define SLOW_TIME_HPP

#include "../PowerUp.hpp"

class SlowTime : public PowerUp {
   public:
    SlowTime(const PowerUpIconArgs& powerUpIconArgs, Player& player);

   private:
    void activate() override;
    void deactivate() override;
};

#endif
