#include "raylib.h"

#define BLOCK_SIZE 64
#define MAX_MAP_WIDTH 30
#define MAX_MAP_HEIGHT 20

enum Directions{
    UP,
    LEFT,
    RIGHT,
    DOWN
}

class Sprite;

Sprite* map[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];

class Sprite{
    protected:
    Texture2D texture;
    int pos_x;
    int pos_y;
    bool walkable;
    int layer;
    public:
    Sprite(Texture2D t, int x, int y, bool w, int l);
    void draw();
    void move(int dx, int dy);
    virtual void action();
};

class Controller : public Sprite{
    Directions facing;
    Rectangle source;
    public:
    Controller();
    void draw();
    void move();
    void act();
};