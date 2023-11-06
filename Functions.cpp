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
#include "Arena.hpp"

using namespace std;

/*Constructor of Champion's class
declare all stats of champion in it*/
Champion::Champion(const string &n, int a, int d, int m, int l)
    : name(n), attack(a), defense(d), magic(m), luck(l), lives(3), score(0) {}

string Champion::getFormattedNameWithAttributes()
{
    return name + " [" + to_string(attack) +
           ", " + to_string(defense) +
           ", " + to_string(magic) +
           ", " + to_string(luck) +
           ", " + to_string(lives) +
           "](points: " + to_string(score) + ")";
}

/*Points wins by a champion*/
void Champion::addScore(int points)
{
    score += points;
}

/*Verify if the champion is eliminated or not*/
bool Champion::isEliminated()
{
    return lives <= 0;
}

/*Verify if a champion has reached the score limit and wins the game*/
bool Champion::hasReachedScoreLimit(int limit)
{
    return score >= limit;
}

void Arena::addChampion(unique_ptr<Champion> c)
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

bool Arena::battle()
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

int randomNumber(int max)
{
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0, max);
    int random_number = uni(rng);
    return random_number;
}
