#include "raylib.h"

#define BLOCK_SIZE 64

class Sprite{
    protected:
    Texture2D texture;
    int pos_x;
    int pos_y;
    bool walkable;
    public:
    Sprite(Texture2D t, int x, int y, bool w);
    draw();
}

