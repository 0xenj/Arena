#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;

class Champion
{
public:
    string name;
    int attack, defense, magic, luck;

    Champion(const string &n, int a, int d, int m, int l)
        : name(n), attack(a), defense(d), magic(m), luck(l) {}
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

int main()
{
    Arena arena;
    int N = 20;
    auto lastChampionTime = chrono::steady_clock::now();
    auto lastBattleTime = chrono::steady_clock::now();

    while (true)
    {
        auto now = chrono::steady_clock::now();

        if (chrono::duration_cast<chrono::seconds>(now - lastChampionTime).count() >= 5)
        {
            Champion newChampion("villain" + to_string(arena.champions.size()), rand() % N, rand() % N, rand() % N, rand() % N);
            arena.addChampion(newChampion);
            lastChampionTime = now;
        }

        if (chrono::duration_cast<chrono::seconds>(now - lastBattleTime).count() >= 1)
        {
            arena.battle();
            lastBattleTime = now;
        }

        this_thread::sleep_for(chrono::milliseconds(100));
    }

    return 0;
}
