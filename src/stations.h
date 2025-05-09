#pragma once
#include "objects.h"

#define CAP_STATION_STORAGE 4
enum HeatDegree{
    LowHeat = 1,
    MediumHeat = 2,
    HighHeat = 3
};
enum StoveSt{
    Off,
    On
};

class Station{
    protected:
    Object* storage[CAP_STATION_STORAGE];
    public:
    Station();
    virtual void use();
    Object* use_obj(int i);
    void put(Object* obj);
    Object* get(int i);
    Object* get(const char* name);
};

class Stove : public Station{
    HeatDegree heat_lvl[CAP_STATION_STORAGE];
    StoveSt state[CAP_STATION_STORAGE];
    int time_on[CAP_STATION_STORAGE];
    public:
    Stove();
    void ch_state(int i);
    void inc_time(int i);
    void ch_heat(HeatDegree h, int i);
    void use();
    void turn_on(int i);
    void turn_off(int i);
};

class Dishwasher : public Station{
    public:
    Dishwasher();
    void use();
};