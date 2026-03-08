#ifndef PET_H
#define PET_H

#include <iostream>
#include <string>

using namespace std;

class Pet
{
public:
    // Constructors, Destructors
    Pet();
    ~Pet();

    // Accessors
    void setWeight(int w);
    int getWeight();

    void setFood(string f);
    string getFood();

    // General methods
    void eat();
    void speak();

protected:
    int weight;
    string food;
};

#endif