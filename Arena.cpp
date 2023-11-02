#include <iostream>
#include <vector>
#include <string>
#include "Arena.hpp"
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;

int main()
{
    int N = 20;
    int i = 0;
    vector<Champions> champions;

    while (i >= 0)
    {
        Champions champion("villain" + to_string(i + 1), rand() % N, rand() % N, rand() % N, rand() % N);

        champions.push_back(champion);

        cout << "Champion " << i << ":" << endl;
        cout << "Name: " << champions[i].name << endl
             << "Attack: " << champions[i].attack << endl
             << "Defense: " << champions[i].defense << endl
             << "Magic: " << champions[i].magic << endl
             << "Luck: " << champions[i].luck << endl
             << endl;

        this_thread::sleep_for(chrono::seconds(2));
        i++;
    }
}
