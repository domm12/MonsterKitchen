#include "raylib.h"
#include "sprite.h"

Sprite::Sprite(Texture2D t, int x, int y, bool w):texture(t), pos_x(x), pos_y(y), walkable(w){}

Sprite::draw(){
    DrawTexture(texture, pos_x, pos_y, WHITE);
}