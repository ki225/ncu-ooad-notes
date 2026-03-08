#ifndef CAT_H
#define CAT_H

#include "Pet.h"

class Cat : public Pet
{
public:
    Cat();
    ~Cat();

    void setNumberToes(int toes);
    int getNumberToes();

private:
    int numberToes;
};

#endif