#include <iostream>
#include <string>

using namespace std;

class Stat {

private:
    int HP_;
    int atk_;
    int def_;
    int crit_;

public:
    Stat(int HP, int atk, int def, int crit);
};