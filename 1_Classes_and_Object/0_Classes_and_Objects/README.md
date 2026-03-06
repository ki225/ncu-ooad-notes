# 類別與物件

## 類別 class
> C++ 為了實現向下兼容來符合 C 語言的操作，它在類別有個很重要的概念就是 class type 必須和 premitive type 的操作是一樣的
> - premitive type: `int`, `char`, `string`, ...

- 定義一個型別 (type)
- 定義 member 和 behavior(function)
- 在 C++ 內，他必須和 premitive type 沒兩樣，也就是 user-defined type 和 built-in type 必須依樣
  - 例如可以宣告變數、傳入函數、回傳值、建立陣列、配置在 stack 或 heap 上
  - 也可以透過 operator overloading 讓 user-defined type 支援 `=`, `+`, `==` 等操作，使其行為接近 built-in type


## 物件 object
- 用 class 建立的變數
- 一個 class 有多個物件
- 每個物件有自己的 memory
- 每個物件都會有自己的一份 member variables
- 但 member functions 在記憶體中只會有一份，所有物件共享同一份函數程式碼

```cpp
class Point {
        int z ;
public:
        int x ;
        int y ;
};
```
物件可以透過 `.` (member access operator) 存取物件的 member variables。
```cpp
Point  p,p1 ;
main() {
     p.x = 100;
     p.y = 200 ;
}
```
- z 是 private（因為 class 預設是 private），因此在 main() 中不能直接存取
- x 和 y 是 public，所以可以直接透過 `p.x`、`p.y` 操作