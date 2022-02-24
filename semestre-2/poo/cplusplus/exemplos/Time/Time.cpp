#include "Time.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::setfill;
using std::setw;

Time::Time(int h, int m, int s) {
    hour = h;
    minute = m;
    second = s;
}

void Time::setTime(int h, int m, int s) {
    hour = h;
    minute = m;
    second = s;
}

int Time::getTimeHour() {
    return hour;
}

int Time::getTimeMinute() {
    return minute;
}

int Time::getTimeSecond() {
    return second;
}

void Time::printUniversal() {
    // Coloca zeros na esquerda, da hora, do minuto e do segundo, até completar dois caracteres.
    cout << setfill('0') << setw(2) << hour << ":" << setw(2) << minute << ":" << setw(2) << second << endl;
}

void Time::printStandard() {
    cout << ((hour == 0 || hour == 12) ? 12 : hour % 12) << ":" 
    << setfill('0') << setw(2) << minute << ":"
    << setw(2) << second << (hour < 12 ? " AM" : " PM") << endl;
}