#pragma once
#include "raylib.h"

#define BLOCK_SIZE 64
#define MAX_MAP_WIDTH 30
#define MAX_MAP_HEIGHT 20

enum Directions{
    UP,
    LEFT,
    RIGHT,
    DOWN
};

class Controller;

class Sprite{
    protected:
    static Texture2D default_texture;
    Texture2D texture;
    int pos_x;
    int pos_y;
    bool walkable;
    int layer;
    public:
    Sprite();
    Sprite(Texture2D t, int x, int y, bool w, int l);
    static void default_texture_load();
    void draw();
    void shift(int dx, int dy);
    void ch_pos(int new_x, int new_y);
    virtual void action();
    friend class Controller;
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