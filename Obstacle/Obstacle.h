
class Obstacle{//for SFML
    protected:
        int x;
        int y;
        int width;
        int height;

    public:
        Obstacle(int x, int y, int width, int height);
        ~Obstacle();
        int getX();
        int getY();
        int getWidth();
        int getHeight();
        void setX(int x);
        void setY(int y);
        void setWidth(int width);
        void setHeight(int height);
        void draw();
};