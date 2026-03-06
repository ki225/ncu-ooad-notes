# Constructor and Destructor
## default constructor
default constructor 是沒有參數的 constructor，當物件被建立時若沒有提供任何參數，編譯器就會呼叫 default constructor 來初始化物件。

如果 class 中沒有定義任何 constructor，編譯器會自動產生一個 compiler-generated default constructor，用來建立物件。但這個自動產生的 constructor 只會做 member-wise initialization，不會進行任何額外邏輯。以下方為例子就只會建立一個大小為 size(A)、類別為 A 的物件 a

```cpp
class A {
    int x;
};

A a;  // compiler automatically generates A()
````

但如果 class 已經定義了任何 constructor，編譯器就不會再自動產生 default constructor，除非程式設計者自行定義。

### Parameterized Constructor

如果有自定義 constructor，在以下情形會發生錯誤
- 自定義 constructor 需要傳入參數，但卻沒有定義一個不需要參數的 construct，此時若直接使用 `Dog puppy;` 建立物件會失敗

```cpp
class Dog {
  public:
    Dog(int x, int y): age=x{};  // Constructor
    ~Dog(); // Destructor

  private:
    int age;
    int weight;
};

int main(){
    Dog puppy;
}
```

在這個例子中 `Dog` 只有一個 **parameterized constructor** (`Dog(int,int)`)，但在建立物件 `Dog puppy;` 時並沒有提供參數，因此編譯器找不到可以呼叫的 constructor，會產生 **compile error**。

原因是 `Dog puppy;` 等同於呼叫 `Dog()`，但 class 並沒有定義 `Dog()`。

### Parameterized Constructor with default arguments

在這個例子中 constructor 的參數有 default arguments，因此當呼叫 `Dog puppy;` 時，編譯器會自動使用預設值 `Dog(2,5)`，因此可以成功建立物件。

```cpp
class Dog {
  public:
    Dog(int x=2, int y=5): age=x{};  // Constructor
    ~Dog(); // Destructor

  private:
    int age;
    int weight;
};

int main(){
    Dog puppy;
}
```

## Destructor

- Destructor 是在物件生命週期結束時自動呼叫的函數，主要用來釋放物件所佔用的資源。
- 特性：
  * 名稱為 `~ClassName`
  * **沒有參數**
  * **沒有回傳型別**
  * 一個 class **只能有一個 destructor**
  * 當物件離開 scope 或被 delete 時會自動呼叫
- 例如：

```cpp
class Dog {
public:
    Dog() { }
    ~Dog() { }
};
```


```cpp
class Dog {
public:
    Dog() {
        data = new int[100];
    }

    ~Dog() {}

private:
    int* data;
};
```

### 自定義 destructor


- destructor 屬於 rule of three
  - rule of three: 
    - 當 class 需要自行管理資源（例如 dynamic memory、file handle、socket 等）時，用來避免資源管理發生錯誤
    - 包含 destructor, copy constructor 與 copy assignment operator
    - 如果 class 自行定義其中一個，通常也需要定義另外兩個，以避免 **default shallow copy** 導致的問題（例如 double free 或 dangling pointer）

在這個例子中 Dog 物件內有 data member，它會指向另一個記憶體區塊，如果沒有特別定義 destructor 釋放 `data`，就會造成 **memory leak**。

```cpp
class Dog {
public:
    Dog() {
        data = new int[100];
    }

    ~Dog() {
        delete[] data;
    }

private:
    int* data;
};
```
destrcutor 只會釋放左邊的記憶體區塊
```
Stack                     Heap
+-----------+             +---------+
| Dog d     |             | int[0]  |
| data -----+------------>| int[1]  |
+-----------+             | ...     |
                          | int[99] |
                          +---------+
```

### 實驗
可以自行編譯&執行[這個檔案](./no-self-defined-destructor.cpp)測試沒有自行定義 destructor 的情況，你會發現在刪除後還可以取得值
```
$ g++ no-self-defined-destructor.cpp -o demo
$ ./demo

Constructor allocated memory at: 0x55a82fdae2b0

Before delete:
address = 0x55a82fdae2b0
value   = 10

After delete:
address = 0x55a82fdae2b0
value   = 10 
```

但如果有自行定義，就會發現存取到的不是 int array
```
$ g++ self-defined-destructor.cpp -o demo
$ ./demo
Constructor allocated memory at: 0x55e1557272b0

Before delete:
address = 0x55e1557272b0
value   = 10
Destructor freeing memory at: 0x55e1557272b0

After delete:
address = 0x55e1557272b0
value   = 1578456871
```

### Destructor 的呼叫時機：

1. **Stack object**
    ```cpp
    Dog d;
    ```
    - 當 `d` 離開 scope 時自動呼叫 destructor。

2. **Heap object**
    ```cpp
    Dog* d = new Dog();
    delete d;
    ```

只有在 `delete` 時 destructor 才會被呼叫，不然就要等到整個程式結束執行。如果忘記 `delete`，destructor 就不會被執行，會造成 memory leak。


