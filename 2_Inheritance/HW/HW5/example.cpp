#include <iostream>
using namespace std;

class A {
public:
   A(){};
   A(int x) {foo=x;}
protected:
    int foo ;
};

class B : A {
public:
    B(){};
    B(int x) : A(x) {};
protected:
    string bar ;
};

int main() {
    B b(100);
    return 0;
}