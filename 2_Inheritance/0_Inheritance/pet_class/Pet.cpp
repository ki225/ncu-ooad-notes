#include "Pet.h"

Pet::Pet() : weight(1), food("Pet Chow") {}

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
