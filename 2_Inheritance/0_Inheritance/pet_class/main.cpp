#include <iostream>
#include "Rat.h"
#include "Cat.h"

using namespace std;

int main()
{
    Rat charles;
    Cat fluffy;

    charles.setWeight(25);

    cout << "Charles weighs "
         << charles.getWeight()
         << " lbs." << endl;

    charles.speak();
    charles.eat();
    charles.sicken();

    fluffy.speak();
    fluffy.eat();

    cout << "Fluffy has "
         << fluffy.getNumberToes()
         << " toes" << endl;

    return 0;
}