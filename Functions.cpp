#include "Arena.hpp"
#include <iostream>

Champions::Champions(string a, int att, int def, int mag, int luc)
{
    name = a;
    attack = att;
    defense = def;
    magic = mag;
    luck = luc;
    cout << name << " enter the Arena "
         << "\n";
}

Champions::~Champions() {}