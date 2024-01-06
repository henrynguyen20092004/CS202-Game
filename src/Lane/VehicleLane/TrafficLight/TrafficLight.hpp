#ifndef TRAFFIC_LIGHT_HPP
#define TRAFFIC_LIGHT_HPP

#include <array>

#include "../../../SpriteNode/SpriteNode.hpp"

class TrafficLight : public SpriteNode {
   public:
    typedef std::unique_ptr<TrafficLight> Ptr;

    enum State {
        Red,
        Yellow,
        Green,
        StateCount,
    };

    TrafficLight(TextureHolder& mTextureHolder, Directions::ID direction, bool isLoading);

    TrafficLight::State getState() const;

   private:
    const std::array<sf::Time, StateCount> mStateTimeCount{
        sf::seconds(2), sf::seconds(1), sf::seconds(3)
    };
    TrafficLight::State mState;
    sf::Time mTimeCount;

    void switchState(TrafficLight::State state);

    void updateCurrent(sf::Time deltaTime) override;

    void saveCurrent(std::ofstream& fout) const final;
    void loadCurrent(std::ifstream& fin) final;
};

#endif
