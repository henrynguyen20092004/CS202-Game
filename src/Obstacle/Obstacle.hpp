#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SFML/Graphics.hpp>

class Obstacle : public sf::Drawable, public sf::Transformable {
   protected:
    float mX;
    float mY;
    float mWidth;
    float mHeight;

   public:
    Obstacle(float x, float y, float width, float height);
    ~Obstacle();

    // Accessors
    float getX() const;       // Get X-coordinate
    float getY() const;       // Get Y-coordinate
    float getWidth() const;   // Get width
    float getHeight() const;  // Get height

    // Mutators
    void setX(float x);            // Set X-coordinate
    void setY(float y);            // Set Y-coordinate
    void setWidth(float width);    // Set width
    void setHeight(float height);  // Set height

    // Draw the obstacle on an SFML window
    void draw(sf::RenderWindow& window) const;

    // Check if the player is colliding with the obstacle
    bool isColliding(const sf::FloatRect& other) const;

    // How to random obstacles in tile map
    // void randomObstacles();
    // void randomObstacles(int numObstacles);

    // How to create obstacles in tile map
    // void createObstacles();
    // void createObstacles(int numObstacles);


};

#endif  // !OBSTACLE_HPP
