#include <string>
using namespace std;

class Champions
{
public:
    string name;
    int attack;
    int defense;
    int magic;
    int luck;
    Champions(string a, int att, int def, int mag, int luc);
    ~Champions();
};
