# Operator Overloading（運算子多載）
Operator Overloading 就是可以替 class 自訂義某些運算符號的行為，透過自定義可以簡化程式的複雜度(可以參考[這篇筆記的範例](https://hackmd.io/@ndhu-programming-2021/BJL0FF_J9))，那它的本質其實像是函數:

### 語法
```c
return_type operator<symbol>(參數);
```
### 範例
```c
double operator + (student& s1, student& s2);  // overloading 二元 + 運算子，回傳值是 double
bool operator==(const Vec& rhs); // overloading == 運算子，回傳值是 bool
Vec& operator=(const Vec& rhs); // overloading 賦值運算子 = ，回傳值是 Vec&
```

## Assignment Operator Overloading
Assignment Operator Overloading 就是我們自定義了 `=` 的功能

### 語法
```cpp
return_type operator = (arguments);
```
例如:
```cpp
void operator = (Foo& a){
    // statements
}
```
### copy assignment operator
- 當一個已存在的物件被另一個已存在的物件賦值 (`=`)，不會自行配置記憶體
  - 若要被賦值的物件本身沒有自行配置記憶體，則當原物件被釋放記憶體時會發生 dangling pointer
- 若沒有自行定義 operator`=` 的操作，compiler 就會自動使用預設 copy assignment operator `Foo& operator=(const Foo& rhs)`，但就是做淺拷貝

範例
```cpp
Table t3
t3 = t2; // copy assignment operator
```
> 它和 copy constructor 有一點像但不一樣，他不會自行配記憶體區塊

### self-defined copy assignment operator
當 class 內部有 pointer 或需要自行管理資源（例如 dynamic memory）時，我們通常需要自行定義 copy assignment operator，避免預設的 member-wise copy 造成 shallow copy 問題。

在自行定義 copy assignment operator 時通常需要注意：
- Self-assignment protection
    - 避免出現
        ```cpp
        a = a;
        ```
    - 解決方法: `if (this != &rhs)` 自行檢查
- 深拷貝 (deep copy)
  - 重新配置新的記憶體並複製資料避免 dangling pointer
    ```cpp
    Foo& Foo::operator=(const Foo& rhs) {
        if (this != &rhs) {              // self-assignment protection
            delete this->bar_;           // 釋放舊資源
            this->bar_ = new Bar(*rhs.bar_); // deep copy
        }
        return *this;
    }
    ```
  - 需要 return 自己
    - copy assignment operator 需要回傳 *this，原因是為了支援 assignment chaining
        > 一開始在[介紹 class ](../0_Classes_and_Objects/README.md)有說 c++ 的 class 建立的型別必須和 premitive type 一樣，所以會需要讓 self-defined 物件能像 int 等原始型態一樣能執行 `a = b = c;`
    - 其實 `a = b = c;` 就是在執行下方動作，若沒有回傳 `*this`，就無法完成這樣的連續賦值操作。
    ```cpp
    b = c
    ↓
    a = (b = c)
    ```

## Ref
- [F.47: Return T& from assignment operators](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#f47-return-t-from-assignment-operators)
