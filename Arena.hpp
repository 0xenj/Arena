#include <string>
using namespace std;

class Champions
{
public:
    string name;
    int attack, defense, magic, luck;
    Champions(const string &n, int att, int def, int mag, int luc);
};

class Arena
{
public:
    vector<Champion> champions;

    void addChampion(const Champion &c)
    {
        if (champions.size() < 4)
        {
            champions.push_back(c);
            cout << c.name << " a rejoint l'arene!" << endl;
        }
        else
        {
            cout << "L'arene est pleine, " << c.name << " ne peut pas rejoindre!" << endl;
        }
    }

    void battle()
    {
        if (champions.size() < 2)
        {
            cout << "Pas assez de champions pour un combat!" << endl;
            return;
        }

        int attackerIndex = rand() % champions.size();
        int defenderIndex;

        do
        {
            defenderIndex = rand() % champions.size();
        } while (attackerIndex == defenderIndex);

        Champion &attacker = champions[attackerIndex];
        Champion &defender = champions[defenderIndex];

        // Ici, ajoutez la logique pour déterminer le gagnant et affichez les résultats du combat
        cout << attacker.name << " attaque " << defender.name << "!" << endl;
    }
};