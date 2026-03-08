# Pointer and Reference
```cpp
char b;
char *p;

p = &b;     // p points to the address of b

print p;    // print the address of b
print *p;   // print the value of b (this is called dereferencing)
```

## Deference in C
```c
struct X {
    int value;
    char b;
};

X m;
X *p;

(*p).value;
p->value; // same as above
```

## How pointer and dereference are implemented
- inderect addressing mode: 先找到位址，再用位址去 memory 取資料
```asm
.data
bVal BYTE 10

mov   esi,   bVal                    ;  ESI = 10 
mov   esi,  OFFSET bVal              ;  ESI = 00404000h  address of bVal 
mov   esi, [esi]                     ; ESI = 10 ;  load from bVal
```
> 比較: Direct addressing
> 指令直接給 memory address
> ```asm
> mov ax, [1000]
> ```


## swap two variables in C (pass by REFERENCE)

```c
main() {
    char x = 10;
    char y = 5;

    swap(&x, &y);
    print x; // 5
    print y; // 10
}

// pass by reference
void swap(char *a, char *b) {
    char temp;
    temp = (*a);
    (*a) = *b;
    (*b) = temp;
}
```

## How to swap two variables in C++? (pass by REFERENCE)
C++ 對物件沒辦法像一般 premitive type 變數一樣用 `&`，因為 reference 在 C++ 代表是某個物件的別名 (alias)，所以在宣告時一定要立即綁定到一個物件，不能像 pointer 一樣先宣告、之後再設定。例如
```cpp
int a = 5;
int &r = a;
```
所以要用 object copy
```cpp
main() {
    A x = 10;
    A y = 5;

    swap(x, y);
    print x; // 5
    print y; // 10
}

void swap(A &a, A &b) {
    char temp;
    temp = a.value;
    a.value = b.value;
    b.value = temp;
}
```

## C++'s pass by REFERENCE

```cpp
class T {
    int value;
    char b;
}

T p;        // create a T-type variable of size(T), there is no pointer or reference
T *q;

q = new T(); // q points to the address of T
```