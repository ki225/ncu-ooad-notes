#include "Cat.h"

Cat::Cat() : numberToes(5) {}

Cat::~Cat() {}

void Cat::setNumberToes(int toes)
{
    numberToes = toes;
}

int Cat::getNumberToes()
{
    return numberToes;
}