#ifndef INCREASE_SCORE_HPP
#define INCREASE_SCORE_HPP

#include "../PowerUp.hpp"

class IncreaseScore : public PowerUp {
   public:
    IncreaseScore(Player& player);

   private:
    void activate() override;
    void deactivate() override;
};

#endif
