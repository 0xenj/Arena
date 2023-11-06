#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <random>
#include <ctime>
#include <chrono>
#include <thread>
#include <algorithm>
#include <memory>

using namespace std;

class Champion
{
public:
    string name;
    int attack, defense, magic, luck, lives, score;

    /*Constructor of Champion's class
    declare all stats of champion in it*/
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

    /*Points wins by a champion*/
    void addScore(int points)
    {
        score += points;
    }

    /*Verify if the champion is eliminated or not*/
    bool isEliminated() const
    {
        return lives <= 0;
    }

    /*Verify if a champion has reached the score limit and wins the game*/
    bool hasReachedScoreLimit(int limit) const
    {
        return score >= limit;
    }
};

class Arena
{
public:
    vector<unique_ptr<Champion>> champions;
    const int ARENA_SIZE = 4;
    const int BATTLE_SIZE = 2;
    const int POINTS_WIN = 5;
    const int POINTS_DRAW = 2;
    const int POINTS_SURVIVE = 2;

    void addChampion(unique_ptr<Champion> c)
    {
        if (champions.size() < ARENA_SIZE)
        {
            cout << c->getFormattedNameWithAttributes() << " a rejoint l'arene!" << endl;
            champions.push_back(move(c));
        }
        else
        {
            cout << "L'arene est pleine, " << c->getFormattedNameWithAttributes() << " ne peut pas rejoindre!" << endl;
        }
    }

    bool battle()
    {
        if (champions.size() < BATTLE_SIZE)
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

        Champion *attacker = champions[attackerIndex].get();
        Champion *defender = champions[defenderIndex].get();

        int attackerWins = 0;
        int defenderWins = 0;

        if (attacker->attack > defender->magic)
            attackerWins++;
        if (defender->attack > attacker->magic)
            defenderWins++;
        if (attacker->magic > defender->defense)
            attackerWins++;
        if (defender->magic > attacker->defense)
            defenderWins++;
        if (attacker->defense > defender->attack)
            attackerWins++;
        if (defender->defense > attacker->attack)
            defenderWins++;

        Champion *winner = nullptr;
        Champion *loser = nullptr;

        if (attackerWins > defenderWins)
        {
            winner = attacker;
            loser = defender;
        }
        else if (defenderWins > attackerWins)
        {
            winner = defender;
            loser = attacker;
        }

        if (loser && loser->luck > winner->luck && rand() % 2 == 0)
        {
            cout << loser->getFormattedNameWithAttributes() << " a de la chance et survit avec " << loser->lives << " vies!" << endl;
            loser->addScore(POINTS_SURVIVE);
            return false;
        }

        if (winner)
        {
            loser->lives--;
            winner->addScore(POINTS_WIN);
            cout << winner->getFormattedNameWithAttributes() << " gagne le combat contre " << loser->getFormattedNameWithAttributes() << ". ";
            cout << loser->getFormattedNameWithAttributes() << " a maintenant " << loser->lives << " vies." << endl;

            if (loser->isEliminated())
            {
                cout << loser->getFormattedNameWithAttributes() << " est elimine de l'arene!" << endl;
                winner->addScore(POINTS_WIN);
                champions.erase(remove_if(champions.begin(), champions.end(),
                                          [loser](const unique_ptr<Champion> &c)
                                          { return c.get() == loser; }),
                                champions.end());
            }
        }
        else
        {
            cout << "Le combat entre " << attacker->getFormattedNameWithAttributes() << " et " << defender->getFormattedNameWithAttributes() << " se termine par un match nul." << endl;
            attacker->addScore(POINTS_DRAW);
            defender->addScore(POINTS_DRAW);
        }

        for (const auto &champion : champions)
        {
            if (champion->hasReachedScoreLimit(100))
            {
                return true;
            }
        }

        return false;
    }
};

int randomNumber(int max)
{
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0, max);
    int random_number = uni(rng);
    return random_number;
}

int main()
{
    {
        Arena arena;
        int i = 0;
        bool combatOver = false;
        auto start = chrono::steady_clock::now();
        int lastChampionAddedAtSecond = -5;

        while (!combatOver)
        {
            auto now = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::seconds>(now - start).count();

            if (elapsed - lastChampionAddedAtSecond >= 5 && arena.champions.size() < 4)
            {
                auto newChampion = make_unique<Champion>("villain" + to_string(i), randomNumber(20), randomNumber(20), randomNumber(20), randomNumber(20));
                arena.addChampion(move(newChampion));
                lastChampionAddedAtSecond = static_cast<int>(elapsed);
                i++;
            }

            combatOver = arena.battle();
            this_thread::sleep_for(chrono::seconds(1));
        }

        cout << "Les combats sont finis!" << endl;

        auto winner = max_element(arena.champions.begin(), arena.champions.end(), [](const unique_ptr<Champion> &a, const unique_ptr<Champion> &b)
                                  { return a->score < b->score; });

        cout << "Le gagnant est : " << (*winner)->getFormattedNameWithAttributes() << endl;

        return 0;
    }
}
