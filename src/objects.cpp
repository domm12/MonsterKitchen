#include <iostream>
#include <typeinfo>
#include <cstring>
#include "objects.h"

using namespace std;

int abs(int a){
    return (a >= 0)? a : -a;
}

Object::Object(const char* n):name(n){}
void Object::roast(int heat){}
void Object::boil(int heat){}
void Object::clean(){}
void Object::ch_temp(int heat){}
void Object::reset(){}
void Object::change_w(int w){}
Ingredient Object::cut(Object* obj, int w){}
void Object::add_spice(Object* obj){}
void Object::inc_time(){}
Object* Object::get(const char* n){}
void Object::put(Object* obj){}
void Object::show(){}
void Object::ch_ing_st(){}
void Object::chop(Object* obj){}
int Object::get_dif(Object* obj){return 0;}
const type_info& Object::type() {
    return typeid(*this);
}
void Object::overwr(){
    cout << "1";
}
ostream& operator<<(ostream& os, const Object& obj) {
    os << obj.name;
    return os;
}

Spice::Spice(const char* n = "air", int w = 0):Object(n), weight(w){}
const type_info& Spice::type() {
    return typeid(Spice);
}
int Spice::get_dif(Object* obj){
    if(!obj || type() != obj->type()) return 10;
    Spice* _obj = static_cast<Spice*>(obj);
    if(strcmp(name, _obj->name) == 0){
        if(abs(_obj->weight - weight) <= 10){
            return abs(_obj->weight - weight);
        }
        else{
            return 10;
        }
    }
    return 10;
}
void Spice::change_w(int w){
    weight = w;
}
void Spice::show(){
    cout << name << " :" << endl;
    cout << "weight - " << weight << "grams" << endl;
}

class Ingredient;

Knife::Knife():Object("knife"), cleanliness(true){}
const type_info& Knife::type() {
    return typeid(Knife);
}
void Knife::roast(int){
    cleanliness = false;
    throw "U just roated a knife";
}
void Knife::boil(int){
    cleanliness = true;
    throw "U just boiled a knife";
}
void Knife::clean(){cleanliness = true;}
int Knife::get_dif(Object* obj){
    if(!obj || type() != obj->type()) return 10;
    Knife* _obj = static_cast<Knife*>(obj);
    if(strcmp(name, _obj->name) == 0){
        if(cleanliness == _obj->cleanliness){
            return 0;
        }
        else{
            return 5;
        }
    }
    return 10;
}

Ingredient::Ingredient(const char* n, StateI st, int rt, int bt, int ew, int w, bool clean):Object(n){
    state = st;
    roast_toughness = rt;
    boil_toughness = bt;
    example_weight = ew;
    weight = w;
    roast_lvl = NoRoast;
    boil_lvl = NoBoil;
    cleanliness = clean;
    cur_spice = 0;
    heat = 0;
}
Ingredient::Ingredient(const char* n, StateI st, int rt, int bt, int ew, int w):Object(n){
    state = st;
    roast_toughness = rt;
    boil_toughness = bt;
    example_weight = ew;
    weight = w;
    roast_lvl = NoRoast;
    boil_lvl = NoBoil;
    cleanliness = false;
    cur_spice = 0;
    heat = 0;
}
const type_info& Ingredient::type() {
    return typeid(Ingredient);
}
void Ingredient::roast(int temp){
    heat += temp;
    if(roast_lvl < heat / roast_toughness){
        switch(heat / roast_toughness){
            case 0:
                roast_lvl = NoRoast;
                break;
            case 1:
                roast_lvl = LowRoast;
                break;
            case 2:
                roast_lvl = MediumRoast;
                break;
            case 3:
                roast_lvl = HighRoast;
                break;
            default:
                roast_lvl = BurnedRoast;
        }
    }
}
void Ingredient::boil(int temp){
    heat += temp;
    if(boil_lvl < heat / boil_toughness){
        switch(heat / boil_toughness){
            case 0:
                boil_lvl = NoBoil;
                break;
            case 1:
                boil_lvl = UnderBoiled;
                break;
            case 2:
                boil_lvl = Boiled;
                break;
            default:
                boil_lvl = OverBoiled;
        }
    }
}
void Ingredient::add_spice(Object* s){
    if(!s || typeid(Spice) != s->type()) throw "You can only use spices to spice the ingredients";
    if(cur_spice < CAP_SPICE_SIZE)
        spices[cur_spice++] = s;
    else  
        throw "spices overflow";
}
void Ingredient::show(){
    cout << name << " :" << endl;
    cout << "weight - "<< weight << "grams" << endl;
    cout << "roast degree - ";
    switch(roast_lvl){
        case NoRoast:
            cout << "not roasted";
            break;
        case LowRoast:
            cout << "low roast";
            break;
        case MediumRoast:
            cout << "medium roast";
            break;
        case HighRoast:
            cout << "high roast";
            break;
        default:
            cout << "burned";
    }
    cout << endl;
    cout << "boil degree - ";
    switch(boil_lvl){
        case NoBoil:
            cout << "not boiled";
            break;
        case UnderBoiled:
            cout << "underboiled";
            break;
        case Boiled:
            cout << "boiled";
            break;
        default:
            cout << "overboiled";
    }
    cout << endl;
    cout << "state - "; 
    switch(state){
        case Solid:
            cout << "solid";
            break;
        case Chopped:
            cout << "chopped";
            break;
        case Mashed:
            cout << "mashed";
            break;
        default:
            cout << "grated";
    }
    cout << endl;
    if(cleanliness){
        cout << "clean";
    }
    else{
        cout << "dirty";
    }
    cout << endl;
    cout << "Spices :"<< endl;
    cout << "-----------" << endl;
    for(int i = 0; i< cur_spice; i++){
        cout << "   ";
        spices[i]->show();
    }
    cout << "-----------" << endl;
}
void Ingredient::overwr(){
    cout << "2";
}
void Ingredient::change_w(int w){
    if(state != StateI::Solid)
        weight = w;
    else
        weight = (w/example_weight)*example_weight;
}
int Ingredient::get_w(){
    return weight;
}
void Ingredient::clean(){cleanliness = true;}
int Ingredient::get_dif(Object* obj){
    if(!obj || type() != obj->type()) return 10;
    Ingredient* _obj = static_cast<Ingredient*>(obj);
    if(strcmp(name, _obj->name) == 0){
        int dif = 0;
        for(int  i = 0; i < cur_spice; i++){
            bool found = false;
            for(int j = 0; j < _obj->cur_spice; j++){
                if(spices[i]->name == _obj->spices[j]->name){
                    dif += spices[i]->get_dif(_obj->spices[i]);
                    found = true;
                    break;
                }
            }
            if(!found) dif += 10;
        }
        dif = dif * 2 / (cur_spice * 10);
        dif += (abs(weight - _obj->weight) < 100) ? abs(weight - _obj->weight) / 50 : 2;
        dif += (cleanliness != _obj->cleanliness);
        dif += (abs((int)roast_lvl - (int)(_obj->roast_lvl)) < 2)? abs((int)roast_lvl - (int)(_obj->roast_lvl)) : 2;
        dif += (abs((int)boil_lvl - (int)(_obj->boil_lvl)) < 2)? abs((int)boil_lvl - (int)(_obj->boil_lvl)) : 2;
        dif += (state != _obj->state);
        return dif;
    }
    return 10;
}

Ingredient Knife::cut(Object* _ing, int w){
    if(!_ing || typeid(Ingredient) != _ing->type()) throw "You can cut only Ingredients";
    Ingredient* ing = to_ingredient(_ing);
    if(w > ing->weight)
        throw "Can't cut more than you have";
    Ingredient leftovers(*ing);
    leftovers.weight -= w;
    ing->weight = w;
    if(!cleanliness){
        leftovers.cleanliness = false;
        ing->cleanliness = false;
    }
    return leftovers;
}
void Knife::chop(Object* _ing){
    if(!_ing || typeid(Ingredient) != _ing->type()) throw "You can chop only Ingredients";
    Ingredient* ing = to_ingredient(_ing);
    if(ing->state == Solid)
        ing->state = Chopped;
}
void Knife::mash(Object* _ing){
    if(!_ing || typeid(Ingredient) != _ing->type()) throw "You can mash only Ingredients";
    Ingredient* ing = to_ingredient(_ing);
    if(ing->state == Solid || ing->state == Chopped)
        ing->state = Mashed;
}
void Knife::grate(Object* _ing){
    if(!_ing || typeid(Ingredient) != _ing->type()) throw "You can grate only Ingredients";
    Ingredient* ing = to_ingredient(_ing);
    if(ing->state == Solid || ing->state == Chopped)
        ing->state = Grated;
}

Utensils::Utensils(const char* n, TypeU t, int hr): Object(n){
    memset(time_cooking, 0, CAP_UTEN_SIZE * sizeof(int));
    cur_size = 0;
    temp = NormalTemp;
    _type = t;
    heat_res = hr;
}
const type_info& Utensils::type() {
    return typeid(Utensils);
}
void Utensils::inc_time(){
    ++(*this);
}
Utensils Utensils::operator ++(){
    for(int i = 0; i < cur_size; i++)
        time_cooking[i]++;
    return *this;
}
Utensils& Utensils::operator ++(int){
    Utensils obj(*this);
    for(int i = 0; i < cur_size; i++)
        time_cooking[i]++;
    return obj;
}
void Utensils::ch_ing_st(){
    if(_type == TypeU::Roast){
        for(int i = 0; i < cur_size; i++){
            insides[i]->roast(temp * 20);
        }
    }
    else if(_type == TypeU::Boil){
        for(int i = 0; i < cur_size; i++){
            insides[i]->boil(temp * 20);
        }
    }
}
void Utensils::put(Object* obj){
    if(cur_size < CAP_UTEN_SIZE)
        insides[cur_size++] = obj;
    else
        throw "Utensils cap reached";
}
Object* Utensils::get(int i){
    if(i >= CAP_UTEN_SIZE) throw "Out of bounds for Utensils";
    Object* obj = insides[i];
    for(int j = i+1; j <= cur_size; j++){
        insides[j-1] = insides[j];
    }
    cur_size--;
    return obj;
}
Object* Utensils::get(const char* _name){
    Object* obj;
    int i = -1;
    for(int j = 0; j < cur_size; j++){
        if(strcmp(insides[j]->name, _name) == 0){
            i = j;
            break;
        }
    }
    if(i == -1) throw "No such object found in Utensils";
    obj = insides[i];
    for(int j = i+1; j < cur_size; j++){
        insides[j-1] = insides[j];
    }
    cur_size--;
    return obj;
}
void Utensils::show(){
    //cout << "Temperature is " << temp << endl;
    cout << "Inside the " << name << " there are:" << endl;
    for(int i = 0; i < cur_size; i++){
        cout << i << ") ";
        insides[i]->show();
    }
}
void Utensils::ch_temp(int heat){
    if(temp < heat / heat_res){
        switch(heat / heat_res){
            case 0:
                temp = NormalTemp;
                break;
            case 1:
                temp = MediumTemp;
                break;
            case 2:
                temp = HighTemp;
                break;
            default:
                temp = ScorchingTemp;
        }
    }
}
void Utensils::reset(){
    memset(time_cooking, 0, CAP_UTEN_SIZE * sizeof(int));
    temp = NormalTemp;
}
int Utensils::get_dif(Object* obj){
    if(!obj || type() != obj->type()) return 10;
    Utensils* _obj = static_cast<Utensils*>(obj);
    int dif = 0;
    for(int  i = 0; i < cur_size; i++){
        dif += insides[i]->get_dif(_obj->insides[i]);
    }
    return dif;
}

Knife* to_knife(Object* obj){
    if(!obj || typeid(Knife) != obj->type()) throw "Unable to convert to Knife";
    Knife* _obj = static_cast<Knife*>(obj);
    return _obj;
}
Ingredient* to_ingredient(Object* obj){
    if(!obj || typeid(Ingredient) != obj->type()) throw "Unable to convert to Ingredient";
    Ingredient* _obj = static_cast<Ingredient*>(obj);
    return _obj;
}
Spice* to_spice(Object* obj){
    if(!obj || typeid(Spice) != obj->type()) throw "Unable to convert to Spice";
    Spice* _obj = static_cast<Spice*>(obj);
    return _obj;
}
Utensils* to_utensils(Object* obj){
    if(!obj || typeid(Utensils) != obj->type()) throw "Unable to convert to Utensils";
    Utensils* _obj = static_cast<Utensils*>(obj);
    return _obj;
}

/*int main(){
    Object obj("Object");
    Knife _knife;
    Spice pepper("pepper", 10);
    Ingredient carrot("carrot", Solid, 100, 140, 250, 560, false);
    Ingredient potato("potato", Solid, 100, 200, 180, 700, false);
    Utensils pot("pot", Boil, 50);
    Ingredient *pcarrot = &carrot;
    Ingredient *ppotato = &potato;
    pot.put(pcarrot);
    pot.put(ppotato);
    pot.show();
    cout << (pcarrot == pot.get(0)) << endl;
    pot.show();
    Object *po = &_knife;
    try{po->boil(1);}
    catch(const char* s){cout << s << endl;}
    return 0;
}*/