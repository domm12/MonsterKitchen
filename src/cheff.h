#pragma once
#include "objects.h"
#include "stations.h"

#define CAP_INVENTORY 20
#define NAME_LEN 20
#define DISH_SIZE 10
#define MAX_SANITY 100

class Cheff{
    Object* inventory[CAP_INVENTORY];
    int cur_inv;
    const char *name;
    int sanity;
    Object* dish[DISH_SIZE];
    int cur_dish;
    static const char* funnyLine;
    public:
    Cheff(const char* n);
    void use_station(Station* s);
    int serve(Object* (&example_dish)[DISH_SIZE], int size);
    static void say_funny();
    Object* use(int i);
    Object* use(const char* _name);
    void take(Object* obj);
    void gather_dish(const char* _name);
    void show_dish();
    void put(int i, Object* uten);
    void put(const char* _name, Object* uten);
    void put(int i, Station* st);
    void put(const char* _name, Station* st);
};