#include <iostream>
#include "Rat.h"

using namespace std;

Rat::Rat() {}

Rat::Rat(int w) : Pet(w) {}

Rat::Rat(int w, string f) : Pet(w, f) {}

Rat::~Rat() {}

void Rat::sicken()
{
    cout << "Speading Plague" << endl;
}