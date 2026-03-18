#include <iostream>

class Base {
    virtual void method() {std::cout << "from Base" << std::endl;}
public:
    virtual ~Base() {method();}
    void baseMethod() {method();}
};

class A : public Base {
    virtual void method() {std::cout << "from A" << std::endl;}
public:
    virtual ~A() {method();}
};

int main() {
    Base* base = new A();
    base->baseMethod();
    delete base;
    return 0;
}