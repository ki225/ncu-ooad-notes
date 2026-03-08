#include <iostream>
#include "Pet.h"

using namespace std;

Pet::Pet() : weight(1), food("Pet Chow") {}

Pet::Pet(int w) : weight(w), food("Pet Chow") {}

Pet::Pet(int w, string f) : weight(w), food(f) {}

Pet::~Pet() {}

void Pet::setWeight(int w)
{
    weight = w;
}

int Pet::getWeight()
{
    return weight;
}

void Pet::setFood(string f)
{
    food = f;
}

string Pet::getFood()
{
    return food;
}

void Pet::eat()
{
    cout << "Eating " << food << endl;
}

void Pet::speak()
{
    cout << "Growl" << endl;
}