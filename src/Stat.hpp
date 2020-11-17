#include <iostream>
#include <string>

using namespace std;

class Stat {

private:
    int maxHP_;
    int HP_;
    int atk_;
    int def_;
    int crit_;

public:
    Stat(int maxHP, int HP, int atk, int def, int crit);

    Stat& operator+=(const Stat& b);
};

Stat operator+(const Stat &a, const Stat &b);