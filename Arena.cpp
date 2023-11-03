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
    int attack, defense, magic, luck, lives;

    Champion(const string &n, int a, int d, int m, int l)
        : name(n), attack(a), defense(d), magic(m), luck(l), lives(3) {}

    string getFormattedNameWithAttributes() const
    {
        return name + " [" + to_string(attack) +
               "," + to_string(defense) +
               "," + to_string(magic) +
               "," + to_string(luck) +
               "](" + to_string(lives) + ")";
    }
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
            cout << c.getFormattedNameWithAttributes() << " a rejoint l'arene!" << endl;
        }
        else
        {
            cout << "L'arene est pleine, " << c.getFormattedNameWithAttributes() << " ne peut pas rejoindre!" << endl;
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

        int attackerWins = 0;
        int defenderWins = 0;

        // Confrontation 1: Attaque vs Magie
        if (attacker.attack > defender.magic)
            attackerWins++;
        if (defender.attack > attacker.magic)
            defenderWins++;

        // Confrontation 2: Magie vs Défense
        if (attacker.magic > defender.defense)
            attackerWins++;
        if (defender.magic > attacker.defense)
            defenderWins++;

        // Confrontation 3: Défense vs Attaque
        if (attacker.defense > defender.attack)
            attackerWins++;
        if (defender.defense > attacker.attack)
            defenderWins++;

        Champion *winner = nullptr;
        Champion *loser = nullptr;

        if (attackerWins > defenderWins)
        {
            winner = &attacker;
            loser = &defender;
        }
        else if (defenderWins > attackerWins)
        {
            winner = &defender;
            loser = &attacker;
        }

        if (loser && loser->luck > winner->luck)
        {
            if (rand() % 2 == 0)
            { // 50% chance
                cout << loser->getFormattedNameWithAttributes() << " a de la chance et survit avec " << loser->lives << " vies!" << endl;
                return;
            }
        }

        if (winner)
        {
            loser->lives--;
            cout << winner->getFormattedNameWithAttributes() << " gagne le combat contre " << loser->getFormattedNameWithAttributes() << ". ";
            cout << loser->getFormattedNameWithAttributes() << " a maintenant " << loser->lives << " vies." << endl;
            if (loser->lives <= 0)
            {
                cout << loser->getFormattedNameWithAttributes() << " est elimine de l'arene!" << endl;
                champions.erase(champions.begin() + (loser - &champions[0])); // Remove the champion who lost all lives
            }
        }
        else
        {
            cout << "Le combat entre " << attacker.getFormattedNameWithAttributes() << " et " << defender.getFormattedNameWithAttributes() << " se termine par un match nul." << endl;
        }
    }
};

int main()
{
    srand(static_cast<unsigned int>(time(nullptr))); // Initialisation du générateur de nombres aléatoires
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
