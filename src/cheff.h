#pragma once
#include "objects.h"
#include "stations.h"

#define CAP_INVENTORY 20
#define NAME_LEN 20
#define MEAL_SIZE 4
#define MAX_SANITY 100

class Cheff{
    Object* inventory[CAP_INVENTORY];
    int cur_inv;
    const char *name;
    int sanity;
    Object* meal[MEAS_SIZE];
    int cur_meal;
    static const char* funnyLine;
    public:
    Cheff(const char* n);
    void use_station(Station* s);
    int serve(Object* (&example_meal)[MEAL_SIZE], int size);
    static void say_funny();
    Object* use(int i);
    Object* use(const char* _name);
    void take(Object* obj);
    void gather_meal(const char* _name);
    void show_meal();
    void put(int i, Object* uten);
    void put(const char* _name, Object* uten);
    void put(int i, Station* st);
    void put(const char* _name, Station* st);
};