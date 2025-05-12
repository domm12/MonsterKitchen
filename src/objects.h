#pragma once
#include <typeinfo>
#include "sprite.h"
using namespace std;

#define CAP_UTEN_SIZE 10
#define CAP_SPICE_SIZE 5
enum StateI{
    Solid,
    Chopped,
    Mashed,
    Grated,
    Liquid
};
enum RoastDegree{
    NoRoast,
    LowRoast,
    MediumRoast,
    HighRoast,
    BurnedRoast
};
enum BoilDegree{
    NoBoil,
    UnderBoiled,
    Boiled,
    OverBoiled
};
enum Temperature{
    NormalTemp,
    MediumTemp,
    HighTemp,
    ScorchingTemp
};
enum TypeU{
    Roast,
    Boil
};
class Ingredient;

class Object : Sprite{
    public:
    const char* name;
    Object(const char* n);
    virtual void roast(int heat);
    virtual void boil(int heat);
    virtual void clean();
    virtual void ch_temp(int heat);
    virtual void reset();
    virtual void inc_time();
    virtual void show();
    virtual void change_w(int w);
    virtual void ch_ing_st();
    virtual Object* get(const char* n);
    virtual void put(Object* obj);
    virtual void add_spice(Object* obj);
    virtual void chop(Object* obj);
    virtual Ingredient cut(Object* obj, int w);
    virtual int get_dif(Object* obj);
    virtual const type_info& type();
};

class Spice : public Object {
    int weight;
    public:
    Spice(const char* n, int w);
    int get_dif(Object* obj);
    void change_w(int w);
    const type_info& type();
    void show();
};

class Knife : public Object {
    bool cleanliness;
    public:
    Knife();
    void roast(int);
    void boil(int);
    void clean();
    Ingredient cut(Object* ing, int w);
    void chop(Object* ing);
    void mash(Object* ing);
    void grate(Object* ing);
    int get_dif(Object* obj);
    const type_info& type();
};

class Ingredient : public Object {
    int weight;
    bool cleanliness;
    StateI state;
    RoastDegree roast_lvl;
    BoilDegree boil_lvl;
    Object* spices[CAP_SPICE_SIZE];
    int cur_spice;
    int heat;
    int example_weight;
    int roast_toughness;
    int boil_toughness;
    public:
    Ingredient(const char* n, StateI st, int rt, int bt, int ew, int w, bool clean);
    void roast(int heat);
    void boil(int heat);
    void clean();
    void add_spice(Object* s);
    void change_w(int w);
    int get_w();
    void show();
    friend Ingredient Knife::cut(Object* ing, int w);
    friend void Knife::chop(Object* ing);
    friend void Knife::mash(Object* ing);
    friend void Knife::grate(Object* ing);
    int get_dif(Object* obj);
    const type_info& type();
};

class Utensils : public Object {
    Object* insides[CAP_UTEN_SIZE];
    int cur_size;
    Temperature temp;
    int time_cooking[CAP_UTEN_SIZE];
    TypeU _type;
    int heat_res;
    public:
    Utensils(const char* n, TypeU t, int hr);
    void ch_ing_st();
    void ch_temp(int heat);
    void put(Object* obj);
    Object* get(int i);
    Object* get(const char* _name);
    void reset();
    void show();
    void inc_time();
    Utensils operator ++();
    Utensils& operator ++(int);
    int get_dif(Object* obj);
    const type_info& type();
};

Knife* to_knife(Object* obj);
Ingredient* to_ingredient(Object* obj);
Spice* to_spice(Object* obj);
Utensils* to_utensils(Object* obj);
