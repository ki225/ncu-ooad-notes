// main.c
#include <stdio.h>
#include "mylib.h"

int main() {
    int result = add(3, 4);  // external reference
    printf("Result = %d\n", result);
    return 0;
}