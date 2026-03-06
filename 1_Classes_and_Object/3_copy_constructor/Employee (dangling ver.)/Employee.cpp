#include "Employee.h"
#include <cstring>
#include <iostream>

Employee::Employee(char *name, int id) {
    _id = id;
    _name = new char[strlen(name) + 1]; // add 1 for '\0' to end of string
    // Allocates an character array object
    strcpy(_name, name);
}

Employee::~Employee() {
    delete[] _name;
    std::cout << "delete object" << std::endl;
}

char *Employee::getName() {
    return _name;
}

int Employee::getId() {
    return _id;
}