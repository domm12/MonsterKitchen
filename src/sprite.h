#include "raylib.h"

#define BLOCK_SIZE 64
#define MAX_MAP_WIDTH 30
#define MAX_MAP_HEIGHT 20

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
    virtual void use();
}

class Controller : public Sprite{
    public:
    Controller();
    void move();
}