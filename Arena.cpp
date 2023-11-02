#include <iostream>
#include <vector>
#include <string>
#include "Arena.hpp"
#include <cstdlib>

using namespace std;

int main()
{
    int N = 20;
    vector<Champions> champions;

    for (int i = 0; i < 5; i++)
    {
        // Création d'un nouveau champion
        Champions champion("villain" + to_string(i), rand() % N, rand() % N, rand() % N, rand() % N);

        // Ajout du champion au vecteur
        champions.push_back(champion);

        // Affichage des attributs du champion
        cout << "Champion " << i << ":" << endl;
        cout << "Name: " << champions[i].name << endl
             << "Attack: " << champions[i].attack << endl
             << "Defense: " << champions[i].defense << endl
             << "Magic: " << champions[i].magic << endl
             << "Luck: " << champions[i].luck << endl
             << endl;
    }
}
