#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP
#include <SFML/Graphics.hpp>
class Obstacle{//for SFML
    protected:
        float mX;
        float mY;
        float mWidth;
        float mHeight;

    public:
        Obstacle(float mX, float mY, float mWidth, float mHeight);
        ~Obstacle();
        // int getX();
        // int getY();
        // int getWidth();
        // int getHeight();
        // void setX(int x);
        // void setY(int y);
        // void setWidth(int width);
        // void setHeight(int height);
        void draw(sf::RenderWindow& window) const;

};
#endif // !OBSTACLE_HPP