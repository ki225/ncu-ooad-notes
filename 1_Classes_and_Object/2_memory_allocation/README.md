# Memory Allocation
## program 變數記憶體分配
一個 process 的記憶體配置簡單來說如下

> 實際上不同 OS 會略有差異，但概念相同
```
High Address
+-------------+
|   Kernel    | 
+-------------+
|   Stack     | ↓ grows downward
+-------------+
|             |
|             |
|   Heap      | ↑ grows upward
+-------------+
|   BSS       | (uninitialized global)
+-------------+
|   Data      | (initialized global)
+-------------+
|   Text      | (program code)
+-------------+
Low Address
```

> [!important]
> 其中 Data segment 又可細分為：
> 1. Data segment：已初始化的 global / static 變數
> 2. BSS segment：未初始化的 global / static 變數

### Stack
- Stack 主要用於 函數呼叫與區域變數儲存
- 特性：
  - 儲存 local variables
  - 儲存 function call frame
  - 由高位址往低位址成長（向下成長）
  - 當 function return 時會自動釋放記憶體
```c
void foo() {
    int a = 5;   // stack variable
}
```

### Data
- Data segment 儲存 global / static variables
- 特性
  - program 啟動時就配置
  - 整個 process 存活期間都存在
  - process 結束時由 OS 釋放
```c
int g = 10;        // global variable
static int s = 5;  // static variable
```

### Heap
- Heap 用於 動態記憶體配置 (Dynamic Memory Allocation)
  - In C:  `malloc`, `calloc`, `free`
  - In C++: `new`, `delete`
- 特性：
  - 程式執行時才配置
  - 由低位址往高位址成長
  - 必須手動釋放，或是直到整個 process 結束自動釋放
    - 如果系統需要長期執行 process 就很有可能發生 heap 的記憶體長超過 stack 的問題，此時 heap 記憶體配置失敗會導致 C++ throw exception `std::bad_alloc`

#### 範例
下面程式會發生一個問題，當有其他函數呼叫 foo() 函數時，由於 mazda 物件在 foo() 函數執行完畢後就釋放區域變數 mazda 的記憶體區塊，因此所取得的位址實際上是指向的區塊並非 mazda 的
```c
Car* foo() {
    Car  mazda ;
        :
        :
    return &mazda ;
}
```
解決方法是在 foo() 內呼叫 new 來動態配置記憶體區塊，並由我們決定何時釋放空間
```c
Car* foo() {
    Car*  mazda - new Car();
        :
        :
    return mazda ;
}
```

## Dynamic Memory Allocation
因為在真正執行系統的時候我們無法預先知道要分配多少，好比說一個網頁我們無法預期他今天會有多少人造訪，所以必須在 runtime 才動態去根據當時的情況來分配，避免資源浪費或不足。

在 C++ 裡我們可以用 new 的方式來動態配置記憶體，這等同於 C 的 malloc，不過 C++ 在這邊做了優化是 new 會自動呼叫物件的 constructor 進行初始化，並回傳正確型別的 pointer，而 malloc 只負責配置 raw memory，不會呼叫 constructor，這就是 new 和 malloc 的不同之處
```cpp
int *IDpt = new int;            // (in C) int *IDpt = malloc(sizeof(int));
float *theMoney = new float; 
char *letter = new char; 
```
C++ 中 `new` 會回傳它動態配置的區塊的起始記憶體位址，而這塊記憶體區塊是 heap 區塊。
```cpp
int *IDpt = new int; 
*IDpt = 5;  
int *IDpt = new int(5);         // Allocates an int object and initializes it to value 5. 
char *letter = new char('J'); 
```
```cpp
delete IDpt; 
delete theMoney; 
delete letter; 
```
若忘記呼叫 `delete`，該記憶體將持續存在於 heap 中直到 process 結束，這會造成 memory leak。

> 執行 `new()` 是有可能失敗的，會噴 exception (如同前面 heap 章節所述)
## Dynamic allocated array
`new int[1024]` 會配置一塊可以存放 1024 個 int 的連續記憶體空間，而 `new int(1024)` 則只配置 一個 int 物件並將其初始化為 1024。
> 他們長太像了
```cpp
int *pt = new int[1024];    //allocates an array of 1024 ints
double *myBills = new double[10000];

int *pt = new int[1024];    //allocates an array of 1024 ints
int *pt = new int(1024);    //allocates a single int with value 1024 
```

假設有個物件 Table，要使用物件型態去建立陣列但沒有給每一個 elements 做初始化，則會預設替每一個 element 呼叫 default constructor 來初始化物件，以下面為例就會呼叫 `Table()`。但這邊有個問題是我們建立的 Table class 唯一的 constructor 需要參數，
> 由於 Table 並沒有定義 default constructor (`Table()`)，因此編譯器無法建立 Table tbl[10]，這會導致 compile error。
```cpp
class Table {
    Table(int a):num=a{}; // constructor
    int num;
}

Table tbl[10];  // constructor Table() will be called 10 times
delete[] tbl ;
```

後續若要修改陣列元素的內容，就需要透過 index 存取
```cpp
int *buff = new int[1024]; 
for (i = 0; i < 1024; i++) { 
    buff[i] = 52; 	// Assigns 52 to each element; 
    buff++; 
}
```
記得使用 `delete[]` 釋放。當使用 `new[]` 配置陣列時，必須使用 `delete[]` 釋放，因為 `delete[]` 會逐一呼叫每個物件的 destructor；若錯誤地使用 `delete`，可能會造成 undefined behavior。
```cpp
delete[] pt; 
delete[] myBills;  
```