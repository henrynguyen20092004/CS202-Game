#ifndef JUMP_HPP
#define JUMP_HPP

#include "../PowerUp.hpp"

class Jump : public PowerUp {
   public:
    Jump(Player& player);

   private:
    void activate() override;
    void deactivate() override;
};

#endif
