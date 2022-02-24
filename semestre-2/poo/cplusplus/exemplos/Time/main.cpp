#include "Time.cpp"
#include <iostream>

using std::cout;
using std::endl;

int main() {

    Time *t = new Time(15,32,24);
    t->printUniversal();
    t->printStandard();
    
    cout << endl;

    Time *t2 = new Time(8,6,3);
    t2->printUniversal();
    t2->printStandard();
}