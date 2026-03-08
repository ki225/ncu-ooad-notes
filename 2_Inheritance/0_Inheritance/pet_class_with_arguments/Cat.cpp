#include "Cat.h"

Cat::Cat() : numberToes(5) {}

Cat::Cat(int w) : Pet(w), numberToes(5) {}

Cat::Cat(int w, string f) : Pet(w, f), numberToes(5) {}

Cat::Cat(int w, string f, int toes) : Pet(w, f), numberToes(toes) {}

Cat::~Cat() {}

void Cat::setNumberToes(int toes)
{
    numberToes = toes;
}

int Cat::getNumberToes()
{
    return numberToes;
}