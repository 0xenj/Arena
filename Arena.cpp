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
