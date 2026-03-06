#include <iostream>
#include "Employee.h"

int main() {
    Employee programmer("John", 22);
    std::cout << programmer.getName() << std::endl;

    // Lots of code here

    Employee manager = programmer;

    delete &programmer;
    return 0;
}