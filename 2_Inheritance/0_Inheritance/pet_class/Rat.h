#ifndef RAT_H
#define RAT_H

#include "Pet.h"

class Rat : public Pet
{
public:
    Rat();
    ~Rat();

    void sicken();
};

#endif