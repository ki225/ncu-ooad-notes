#include <iostream>
using namespace std;

class A {
public:
    A(){}; // constructor
    void foo() {cout << "A::foo()" << endl;}
    int bar() {cout << "A::bar()" << endl; return 1;}
};

class B:A {
public:
    B(){}; // constructor
    void foo() {cout << "B::foo()" << endl;}
    char bar() {cout << "B::bar()" << endl; return 'x';}
};

int main() {
    // call A class constructor first, then call B's
    B b; 

    // B class's foo() override A's
    b.foo(); // output "B::foo()"

    // since char bar() and int bar() are not same, it's not override or overload issue
    b.bar(); // output "B::bar()"
}