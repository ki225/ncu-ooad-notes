#include <iostream>
using namespace std ;

class pet {
public:
    pet() { cout << "pet constructor" << endl; }
    ~pet() { cout << "pet destructor" << endl; }
    void speak() { cout << "Growl " << endl; }
};

class cat : public pet {
public:
    cat() { cout << "cat constructor" << endl; }
    ~cat() { cout << "cat destructor" << endl; }

    void speak() { cout << "meow" << endl; } 
    int* return_a_addr() { return &a; }
    int a;
};


int main() {
    pet insect;
    cat pussy;
    pet *nose = (pet *)new cat();   // polymorphism

    insect.speak();
    pussy.speak();
    ((pet)pussy).speak();  // no feature of polymorphism
    nose->speak();
}