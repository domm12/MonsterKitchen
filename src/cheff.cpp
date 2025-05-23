#include <iostream>
#include <cstring>
#include "cheff.h"

using namespace std;

Cheff::Cheff(const char* n): name(n), cur_inv(0), sanity(MAX_SANITY), cur_meal(0){}
const char* Cheff::funnyLine = "Mario";

void Cheff::use_station(Station* s){
    s->use();
}
int Cheff::serve(Object* (&example_meal)[MEAL_SIZE], int size){
    int dif = 0;
    for(int i = 0; i < MEAL_SIZE; i++){
        if(i < cur_meal && i < size){
            dif += meal[i]->get_dif(example_meal[i]);
        }
        else if(i < cur_meal) {
            dif += 10;
        }
        else{
            break;
        }
    }
    return dif / cur_meal;
}
void Cheff::say_funny(){
    cout << funnyLine << endl;
}
void Cheff::take(Object* obj){
    if(cur_inv < CAP_INVENTORY)
        inventory[cur_inv++] = obj;
    else
        throw "Inventory cap reached";
}
Object* Cheff::use(int i){
    if(i >= cur_inv) throw "Out of bounds for inventory";
    return inventory[i];
}
Object* Cheff::use(const char* _name){
    int i = -1;
    for(int j = 0; j < cur_inv; j++){
        if(strcmp(inventory[j]->name, _name) == 0){
            i = j;
            break;
        }
    }
    if(i == -1) throw "Not found in the inventory";
    return inventory[i];
}
void Cheff::show_meal(){
    for(int i = 0; i < cur_meal; i++){
        meal[i]->show();
    }
}
void Cheff::gather_meal(const char* _name){
    int i = -1;
    for(int j = 0; j < cur_inv; j++){
        if(strcmp(inventory[j]->name, _name) == 0){
            i = j;
            break;
        }
    }
    if(i == -1) throw "Not found in the inventory for meal";
    if(cur_meal >= MEAL_SIZE) throw "Too big of a meal";
    meal[cur_meal++] = inventory[i];
    for(int j = i+1; j < cur_inv; j++){
        inventory[j-1] = inventory[j];
    }
    cur_inv--;
}
void Cheff::put(int i, Object* _uten){
    if(!_uten || typeid(Utensils) != _uten->type()) throw "You can only put into Utensils";
    Utensils* uten = to_utensils(_uten);
    if(i >= cur_inv) throw "Out of bounds for inventory";
    uten->put(inventory[i]);
    for(int j = i+1; j < cur_inv; j++){
        inventory[j-1] = inventory[j];
    }
    cur_inv--;
}
void Cheff::put(const char* _name, Object* _uten){
    if(!_uten || typeid(Utensils) != _uten->type()) throw "You can only put into Utensils";
    Utensils* uten = to_utensils(_uten);
    int i = -1;
    for(int j = 0; j < cur_inv; j++){
        if(strcmp(inventory[j]->name, _name) == 0){
            i = j;
            break;
        }
    }
    if(i == -1) throw "No such object in the inventory";
    uten->put(inventory[i]);
    for(int j = i+1; j < cur_inv; j++){
        inventory[j-1] = inventory[j];
    }
    cur_inv--;
}
void Cheff::put(int i, Station* st){
    if(i >= cur_inv) throw "Out of bounds for inventory";
    st->put(inventory[i]);
    for(int j = i+1; j < cur_inv; j++){
        inventory[j-1] = inventory[j];
    }
    cur_inv--;
}
void Cheff::put(const char* _name, Station* st){
    int i = -1;
    for(int j = 0; j < cur_inv; j++){
        if(strcmp(inventory[j]->name, _name) == 0){
            i = j;
            break;
        }
    }
    if(i == -1) throw "No such object in the inventory";
    st->put(inventory[i]);
    for(int j = i+1; j < cur_inv; j++){
        inventory[j-1] = inventory[j];
    }
    cur_inv--;
}