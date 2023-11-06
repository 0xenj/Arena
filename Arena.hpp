#include <string>
#include <vector>
#include <memory>

using namespace std;

class Champion
{
public:
    string name;
    int attack, defense, magic, luck, lives, score;

    /*Constructor of Champion's class
    declare all stats of champion in it*/
    Champion(const string &n, int a, int d, int m, int l);

    string getFormattedNameWithAttributes();

    /*Points wins by a champion*/
    void addScore(int points);

    /*Verify if the champion is eliminated or not*/
    bool isEliminated();

    /*Verify if a champion has reached the score limit and wins the game*/
    bool hasReachedScoreLimit(int limit);
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

    void addChampion(unique_ptr<Champion> c);

    bool battle();
};

int randomNumber(int max);