#include "SettingsState.hpp"

SettingsState::SettingsState(StateStack& stack, Context context)
    : State(stack, context) {
    mBackgroundSprite.setTexture(
        context.textureHolder->get(Textures::ID::MenuBackground)
    );
    
}