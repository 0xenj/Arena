#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <algorithm>

using namespace std;

class Champion
{
public:
    string name;
    int attack, defense, magic, luck, lives, score;

    Champion(const string &n, int a, int d, int m, int l)
        : name(n), attack(a), defense(d), magic(m), luck(l), lives(3), score(0) {}

    string getFormattedNameWithAttributes() const
    {
        return name + " [" + to_string(attack) +
               ", " + to_string(defense) +
               ", " + to_string(magic) +
               ", " + to_string(luck) +
               ", " + to_string(lives) +
               "](points: " + to_string(score) + ")";
    }

    void addScore(int points)
    {
        score += points;
    }

    bool hasReachedScoreLimit(int limit) const
    {
        return score >= limit;
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

    bool battle()
    {
        if (champions.size() < 2)
        {
            cout << "Pas assez de champions pour un combat!" << endl;
            return false;
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

        // Confrontations
        if (attacker.attack > defender.magic)
            attackerWins++;
        if (defender.attack > attacker.magic)
            defenderWins++;
        if (attacker.magic > defender.defense)
            attackerWins++;
        if (defender.magic > attacker.defense)
            defenderWins++;
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

        // Surviving by luck
        if (loser && loser->luck > winner->luck && rand() % 2 == 0)
        {
            cout << loser->getFormattedNameWithAttributes() << " a de la chance et survit avec " << loser->lives << " vies!" << endl;
            loser->addScore(5);
            return false;
        }

        if (winner)
        {
            loser->lives--;
            winner->addScore(10);
            cout << winner->getFormattedNameWithAttributes() << " gagne le combat contre " << loser->getFormattedNameWithAttributes() << ". ";
            cout << loser->getFormattedNameWithAttributes() << " a maintenant " << loser->lives << " vies." << endl;

            if (loser->lives <= 0)
            {
                cout << loser->getFormattedNameWithAttributes() << " est elimine de l'arene!" << endl;
                winner->addScore(5);
                champions.erase(champions.begin() + (loser - &champions[0]));
            }
        }
        else
        {
            cout << "Le combat entre " << attacker.getFormattedNameWithAttributes() << " et " << defender.getFormattedNameWithAttributes() << " se termine par un match nul." << endl;
            attacker.addScore(5);
            defender.addScore(5);
        }

        for (const auto &champion : champions)
        {
            if (champion.hasReachedScoreLimit(100))
            {
                return true;
            }
        }

        return false;
    }
};

void simulateCombat()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    Arena arena;
    int N = 20;
    int i = 0;
    auto lastChampionTime = chrono::steady_clock::now();
    auto lastBattleTime = chrono::steady_clock::now();
    bool scoreLimitReached = false;

    while (!scoreLimitReached)
    {
        auto now = chrono::steady_clock::now();

        if (chrono::duration_cast<chrono::seconds>(now - lastChampionTime).count() >= 5)
        {
            Champion newChampion("villain" + to_string(i), rand() % N, rand() % N, rand() % N, rand() % N);
            arena.addChampion(newChampion);
            lastChampionTime = now;
            i++;
        }

        if (chrono::duration_cast<chrono::seconds>(now - lastBattleTime).count() >= 1)
        {
            arena.battle();
            lastBattleTime = now;
        }

        scoreLimitReached = arena.battle();
        this_thread::sleep_for(chrono::seconds(1));
    }

    cout << "The combat has ended. Final Scores:" << endl;
    for (const auto &champion : arena.champions)
    {
        cout << champion.getFormattedNameWithAttributes() << endl;
    }
}

int main()
{
    simulateCombat();
    return 0;
}
