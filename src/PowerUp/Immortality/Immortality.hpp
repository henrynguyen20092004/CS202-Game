#ifndef IMMORTALITY_HPP
#define IMMORTALITY_HPP

#include "../PowerUp.hpp"

class Immortality : public PowerUp {
   public:
    Immortality(Player& player);

   private:
    void activate() override;
    void deactivate() override;
};

#endif
