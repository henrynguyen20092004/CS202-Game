#ifndef RAILWAY_SIGNAL_HPP
#define RAILWAY_SIGNAL_HPP

#include "../../../SpriteNode/SpriteNode.hpp"

class RailwaySignal : public SpriteNode {
   public:
    typedef std::unique_ptr<RailwaySignal> Ptr;

    enum State {
        Red,
        Green,
    };

    RailwaySignal(TextureHolder& mTextureHolder);

    void switchState(RailwaySignal::State state);
};

#endif
