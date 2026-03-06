#include <iostream>
#include "Employee.h"

int main() {
    Employee programmer("John", 22);
    std::cout << programmer.getName() << std::endl;

    // Lots of code here

    // let John to be manager
    Employee manager = programmer;
    return 0;
}