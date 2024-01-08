#ifndef LOG_HPP
#define LOG_HPP

#include "../MovableSpriteNode/MovableSpriteNode.hpp"

class Log : public MovableSpriteNode {
   public:
    typedef std::unique_ptr<Log> Ptr;

    virtual int getLength() const = 0;

   protected:
    Log(TextureHolder& textureHolder, Textures::ID textureID,
        sf::IntRect textureRect, Directions::ID direction);

   private:
    Directions::ID mDirection;

    void updateCurrent(sf::Time deltaTime) override;

    void saveCurrent(std::ofstream& fout) const final;
    void loadCurrent(std::ifstream& fin) final;
};

#endif
