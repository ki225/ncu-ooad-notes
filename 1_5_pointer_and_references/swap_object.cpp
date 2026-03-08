#include <iostream>
using namespace std;

class A {
public:
    int val;
    // A(int v) : value(v) {}
};

int main() {
    A x;
    A y;
    x.val = 5;
    y.val = 10;
    A &p; // compiler will not allow this

    swap(x, y);
    cout << x.val << endl; // 5
    cout << y.val << endl; // 10
    return 0;
}

void swap(A &a, A &b) {
    int temp;
    temp = a.val;
    a.val = b.val;
    b.val = temp;
}