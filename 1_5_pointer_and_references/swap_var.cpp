# include <iostream>
using namespace std;

// pass by reference
void swap(char *a, char *b) {
    char temp;
    temp = (*a);
    (*a) = *b;
    (*b) = temp;
}

int main() {
    char x = '1';
    char y = '5';

    swap(&x, &y);
    cout << x << endl; // 5
    cout << y << endl; // 10

    return 0;
}

