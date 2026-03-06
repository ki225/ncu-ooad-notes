- 請問 Table 預設的建構式(default constructor)被呼叫了幾次？
  - 2
    - 第一次是 `Table t1;`；再來是 `Table t3;`
    - `Table t2 = t1;` 因為它等同於 `Table t2(t1);`，也就是呼叫 copy constructor
- Table 的解構式(default destructor)被呼叫了幾次？
  - 1
  - 本應執行三次，但三個指向同一個
- What is the final output?
  - 結果如下，是因為沒有寫 copy constructor，所以 C++ 用 default copy constructor (member-wise copy)
    ```
    $ ./test
    constructor
    constructor
    destructor
    free(): double free detected in tcache 2
    Aborted (core dumped)
    ```     

```c
#include <iostream>
using namespace std ;

class Table {
    char *p ;
    int sz ;
public:
    Table(int s=15) { 
        p = new char[100] ;
        cout << "constructor" << endl ;
    } 
    ~Table() { 
        delete[] p ; 
        cout << "destructor" << endl ; 
    }
};

void h() {
    Table t1 ;
    Table t2 = t1 ; 
    Table t3 ;   
    t3 = t2 ;
}

main() {     
    h();   
}

```

## 這個程式的問題
- memory leak
- double free

執行 `Table t2 = t1` 讓兩個 pointer 指向同一塊記憶體
```
t1.p ─┐
      ├────► heap memory A
t2.p ─┘
```

`t3 = t2` 因為沒有特別寫 `operator=` (下一章會提到)，所以 C++ 使用 default assignment (member-wise assignment)，讓結果變成

```
t1.p ─┐
      ├────► heap memory A
t2.p ─┤
t3.p ─┘
```
當 `h()` 結束時依序釋放 t3 -> t2 -> t1 的配置位址，由於三個指向同一個位址，所以執行到 t2 時出現 `double free`，而原先 t3 配置的區塊則不會被回收