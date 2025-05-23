#include <iostream>
#include <cstring>
#include "stations.h"

using namespace std;

Station::Station():storage(), Sprite(){}
void Station::use(){}
Object* Station::use_obj(int i){
    if(i >= CAP_STATION_STORAGE || !storage[i]) throw "There is nothing on that position";
    return storage[i];
}
void Station::put(Object* obj){
    for(int i = 0; i < CAP_STATION_STORAGE; i++){
        if(storage[i] == nullptr){
            storage[i] = obj;
            return;
        }
    }
    throw "Storage cap reached";
}
Object* Station::get(int i){
    if(i >= CAP_STATION_STORAGE) throw "Out of bounds for Station";
    Object* obj = storage[i];
    storage[i] = nullptr;
    return obj;
}
Object* Station::get(const char* name){
    int i = -1;
    for(int j = 0; j < CAP_STATION_STORAGE; j++){
        if(storage[j] && strcmp(storage[j]->name, name) == 0){
            i = j;
            break;
        }
    }
    if(i == -1) throw "No such object found";
    Object* obj = storage[i];
    storage[i] = nullptr;
    return obj;
}

Stove::Stove():time_on(){
        for(int i = 0; i < CAP_STATION_STORAGE; i++){
            state[i] = Off;
            heat_lvl[i] = LowHeat;
        }
    };
void Stove::ch_state(int i){
    if(state[i] && storage[i]){
        storage[i]->ch_temp(heat_lvl[i] * time_on[i]);
    }
} 
void Stove::inc_time(int i){
    if(state[i] && storage[i]){
        time_on[i]++;
        storage[i]->inc_time();
    }
}

void Stove::ch_heat(HeatDegree hd, int i){
    heat_lvl[i] = hd;
}

void Stove::turn_on(int i){
    state[i] = On;
}

void Stove::turn_off(int i){
    if(storage[i]) storage[i]->reset();
    state[i] = Off;
}

void Stove::use(){
    for(int i = 0; i < CAP_STATION_STORAGE; i++){
        inc_time(i);
        if(time_on[i] % 20 == 0){
            ch_state(i);
            if(storage[i])storage[i]->ch_ing_st();
        }
    }
}

Dishwasher::Dishwasher(){}
void Dishwasher::use(){
    for(int i = 0; i < CAP_STATION_STORAGE; i++){
        if(storage[i]) storage[i]->clean();
    }
}