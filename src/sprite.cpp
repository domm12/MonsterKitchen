#include "raylib.h"
#include "sprite.h"

Sprite::Sprite(Texture2D t, int x, int y, bool w):texture(t), pos_x(x), pos_y(y), walkable(w), layer(l){}

void Sprite::draw(){
    DrawTexture(texture, pos_x, pos_y, WHITE);
}

void Sprite::move(int dx, int dy){
    pos_x += dx;
    pos_y += dy;
}

void use(){}

Controller(){}
void Controller::move(){
    if((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && pos_x < MAX_MAP_WIDTH - 1){
        Sprite* new_space = map[pos_y][pos_x + 1];
        if(new_space && new_space.walkable){
            move(1, 0);
        }
    }
    if((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && pos_x > 0){
        Sprite* new_space = map[pos_y][pos_x - 1];
        if(new_space && new_space.walkable){
            move(-1, 0);
        }
    }
    if((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && pos_y > 0){
        Sprite* new_space = map[pos_y - 1][pos_x];
        if(new_space && new_space.walkable){
            move(0, -1);
        }
    }
    if((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && pos_y < MAX_MAP_HEIGHT - 1){
        Sprite* new_space = map[pos_y + 1][pos_x];
        if(new_space && new_space.walkable){
            move(0, 1);
        }
    }
}