# include <stdio.h>

// pass by reference
void swap(char *a, char *b) {
    char temp;
    temp = (*a);
    (*a) = *b;
    (*b) = temp;
}

int main() {
    char x = 10;
    char y = 5;

    swap(&x, &y);
    printf("%d\n", x); // 5
    printf("%d\n", y); // 10

    return 0;
}
