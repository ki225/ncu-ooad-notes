#include <iostream>
#include <vector>

using namespace std;

class Base {
public:
    virtual void print() { cout << "Base" << endl; }
    virtual ~Base() {}
};

class A : public Base {
public:
    virtual void print() { cout << "A" << endl; }
    virtual ~A() {}
};

class B : public Base {
public:
    virtual void print() { cout << "B" << endl; }
    virtual ~B() {}
};

int main(void) {
    vector<Base*> bases = { new Base(), new A(), new B() };
    for (Base* b : bases) {
        b->print();
    }

    for (Base* b : bases) {
        delete b;
        b = nullptr;
    }
    bases.clear();
}
