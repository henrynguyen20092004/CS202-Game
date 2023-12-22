#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>

#include "../../../ResourceHolder/ResourceHolder.hpp"
#include "../Component/Component.hpp"

namespace GUI {

class Button : public Component {
   public:
    typedef std::shared_ptr<Button> Ptr;
    typedef std::function<void()> Callback;

    Button(
        const FontHolder& fontHolder, const TextureHolder& textureHolder,
        const std::string& text
    );

    void setCallback(const Callback& callback);
    void setText(const std::string& text);
    void setToggle(bool flag);

    virtual bool isSelectable() const override;
    virtual void select() override;
    virtual void deselect() override;

    virtual void activate() override;
    virtual void deactivate() override;

    virtual void handleRealTimeInput(
        const sf::Event& event, const sf::RenderWindow& window
    ) override;
    virtual void handleEvent(const sf::Event& event,const sf::RenderWindow& window) override;

    sf::FloatRect getGlobalBounds() const override;

   private:
    const sf::Texture& mNormalTexture;
    const sf::Texture& mSelectedTexture;
    const sf::Texture& mPressedTexture;

    Callback mCallback;
    sf::Sprite mSprite;
    sf::Text mText;
    bool mIsToggle;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}  // namespace GUI

#endif
