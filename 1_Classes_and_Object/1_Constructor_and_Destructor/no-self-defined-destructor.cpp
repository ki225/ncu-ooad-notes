#include <iostream>
using namespace std;

class Dog {
public:
    int* data;

    Dog() {
        data = new int[5];

        for (int i = 0; i < 5; i++) {
            data[i] = i + 10;
        }

        cout << "Constructor allocated memory at: " << data << endl;
    }

};

int* foo() {
    Dog d;
    cout << "\nBefore delete:" << endl;
    cout << "address = " << d.data << endl;
    cout << "value   = " << d.data[0] << endl;

    return d.data;
}

int main() {
    // without destructor

    int* dog_data_addr = foo();

    cout << "\nAfter delete:" << endl;
    cout << "address = " << dog_data_addr << endl;

    // 這是 undefined behavior
    cout << "value   = " << *dog_data_addr << endl;

    return 0;
}