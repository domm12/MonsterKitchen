#include <iostream>
#include <random>
#include "cheff.h"

using namespace std;

int main(){
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(1, 6);
    uniform_int_distribution<mt19937::result_type> dist25(-25, 25);
    uniform_int_distribution<mt19937::result_type> dist50(-50, 50);
    //example meal
    Utensils _bowl("bowl", Boil, 10);
    Spice _curry("curry", 15);
    Spice _chilli("chilli", 10);
    Spice _black_pepper("black pepper", 7);
    Spice _salt("salt", 7);
    Ingredient _rice("rice", Solid, 250, 100, 1, 200, true);
    _rice.boil(200);
    Ingredient _potato("potato", Chopped, 150, 150, 100, 100, true);
    _potato.add_spice(&_curry);
    _potato.add_spice(&_chilli);
    _potato.add_spice(&_salt);
    _potato.boil(300);
    Ingredient _carrot("carrot", Chopped, 150, 150, 100, 100, true);
    _carrot.add_spice(&_curry);
    _carrot.add_spice(&_chilli);
    _carrot.add_spice(&_salt);
    _carrot.boil(300);
    Ingredient _sauce("curry", Liquid, 50, 100, 0, 100, true);
    _sauce.boil(100);
    Ingredient _pork("pork", Chopped, 100, 150, 500, 100, true);
    _pork.add_spice(&_black_pepper);
    _pork.add_spice(&_salt);
    _pork.roast(300);
    //_bowl.put(&_rice);
    //_bowl.put(&_sauce);
    //_bowl.put(&_potato);
    //_bowl.put(&_carrot);
    _bowl.put(&_pork);
    //_bowl.show();
    int ed_size = 1;
    Object* example_meal[MEAL_SIZE];
    example_meal[0] = &_bowl;
    
    //kitchen
    Stove stov;
    mealwasher washer;
    Station crate;
    Station drawer;
    Station table;
    Ingredient pork("pork", Solid, 100, 150, 500, 1000, false);
    Ingredient carrot("carrot", Solid, 150, 150, 100, 600, true);
    Ingredient potato("potato", Chopped, 150, 150, 100, 100, true);
    Ingredient rice("rice", Solid, 250, 100, 1, 1000, true);
    Ingredient sauce("curry", Liquid, 50, 100, 0, 300, true);
    Spice curry("curry", 200);
    Spice chilli("chilli", 200);
    Spice black_pepper("black pepper", 200);
    Spice salt("salt", 500);
    Knife knif;
    Utensils pot("pot", Boil, 300);
    Utensils pan("frying pan", Roast, 150);
    Utensils bowl("bowl", Boil, 10);
    try{
        crate.put(&pork);
        crate.put(&carrot);
        crate.put(&potato);
        crate.put(&rice);
    }
    catch(const char* s) {cout << s << endl;}
    try{
        drawer.put(&curry);
        drawer.put(&chilli);
        drawer.put(&black_pepper);
        drawer.put(&salt);
    }
    catch(const char* s) {cout << s << endl;}
    try{
        table.put(&sauce);
        table.put(&knif);
        table.put(&pot);
        table.put(&pan);
    }
    catch(const char* s) {cout << s << endl;}
    try{
        washer.put(&bowl);
    }
    catch(const char* s) {cout << s << endl;}
    Cheff David("David");
    //cooking
    try{
        David.take(table.get("knife"));
        David.put("knife", &washer);
        David.take(crate.get("pork"));
        David.put("pork", &washer);
        David.use_station(&washer);
        David.take(washer.get("bowl"));
        David.take(washer.get("knife"));
        David.take(washer.get("pork"));
        David.take(drawer.get("salt"));
        David.use("salt")->change_w(5 + (int)dist6(rng));
        David.take(drawer.get("black pepper"));
        David.use("black pepper")->change_w(5 + (int)dist6(rng));
        David.take(table.get("frying pan"));
        David.use("knife")->cut(David.use("pork"), 150 + dist50(rng));
        David.use("knife")->chop(David.use("pork"));

        David.use("pork")->add_spice(David.use("black pepper"));
        David.use("pork")->add_spice(David.use("salt"));
        stov.turn_on(0);
        David.put("frying pan", &stov);
        for(int i  = 0; i < 150; i++) David.use_station(&stov);
        David.put("pork", stov.use_obj(0));
        int tc = (200 + dist50(rng));
        for(int i  = 0; i < tc; i++) David.use_station(&stov);
        David.take(stov.use_obj(0)->get("pork"));
        stov.turn_off(0);
        //David.take(table.get("pot"));
        David.put("pork", David.use("bowl"));
        David.gather_meal("bowl");
        cout << "David's meal" << endl;
        David.show_meal();
        cout << "\n\nExample meal" << endl;
        example_meal[0]->show();
        //David.serve(example_meal, ed_size);
        cout << "\n\nDifference between meales is " << David.serve(example_meal, ed_size) << endl;
    }
    catch(const char* s) {cout << s << endl;}
    return 0;
}