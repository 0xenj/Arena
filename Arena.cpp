#include <iostream>
#include <vector>
#include <string>
#include "Arena.hpp"
#include <cstdlib>

using namespace std;

int main()
{
    Champions champion1("villain1", 10, 3, 4, 8);
    cout << champion1.name << "\n"
         << champion1.attack << "\n"
         << champion1.defense << "\n"
         << champion1.magic << "\n"
         << champion1.luck << "\n";
}