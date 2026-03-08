#ifndef RAT_H
#define RAT_H

#include "Pet.h"

class Rat : public Pet
{
public:
    Rat();
    Rat(int w);
    Rat(int w, string f);
    ~Rat();

    void sicken();
};

#endif