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

void Sprite::action(){}

Controller():facing(UP){
    source = Rectangle(
        (float)(facing * BLOCK_SIZE),
        0,
        (float)BLOCK_SIZE,
        (float)BLOCK_SIZE
    );
}

void Controller::draw(){
    DrawTextureRec(texture, source, {pos_x, pos_y}, WHITE);
}

void Controller::move(){
    bool ch_face = false;
    if((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && pos_x < MAX_MAP_WIDTH - 1){
        Sprite* new_space = map[pos_y][pos_x + 1];
        ch_face = (facing != RIGHT);
        facing = RIGHT;
        if(new_space && new_space->walkable){
            move(1, 0);
        }
    }
    if((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && pos_x > 0){
        Sprite* new_space = map[pos_y][pos_x - 1];
        ch_face = (facing != LEFT);
        facing = LEFT;
        if(new_space && new_space->walkable){
            move(-1, 0); 
        }
    }
    if((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && pos_y > 0){
        Sprite* new_space = map[pos_y - 1][pos_x];
        ch_face = (facing != UP);
        facing = UP;
        if(new_space && new_space.->alkable){
            move(0, -1);
        }
    }
    if((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && pos_y < MAX_MAP_HEIGHT - 1){
        Sprite* new_space = map[pos_y + 1][pos_x];
        ch_face = (facing != DOWN);
        facing = DOWN;
        if(new_space && new_space->walkable){
            move(0, 1);
        }
    }
    if(ch_face){
        source = Rectangle(
            (float)(facing * BLOCK_SIZE),
            0,
            (float)BLOCK_SIZE,
            (float)BLOCK_SIZE
        );
    }
}

void Controller::act(){
    if(IsKeyPressed(KEY_E)){
        new_pos_x = pos_x;
        new_pos_y = pos_y;
        switch(facing){
            case UP:
                new_pos_y -= 1;
                break;
            case LEFT:
                new_pos_x -= 1;
                break;
            case RIGHT:
                new_pos_x += 1;
                break;
            case DOWN:
                new_pos_y += 1;
                break;
        }
        if(new_pos_x >= MAX_MAP_WIDTH || new_pos_x < 0 || new_pos_y >= MAX_MAP_HEIGHT || new_pos_y < 0) return;
        Sprite* new_space = map[new_pos_y][new_pos_x];
        if(new_space){
            new_space->action();
        }
    }
}