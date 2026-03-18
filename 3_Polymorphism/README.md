# PolyMorphism

## What is PolyMorphism
- Polymorphism in C++ is exhibited by the ability of a pointer or reference to a base class type to behave in different ways when it is used to manipulate objects of different subtypes of that base class. 
- 多形就是當你可以用基底 class 的指標或參考來進行處理時，卻可以依照其 subtype 來進行不一樣的事情
- 舉例
  - Base class 是 Shape，他底下有 box, circle, rectangle 等其他 sub class
  - 以 base class 去宣告 paintall 函數，但最後這個函數所實現的操作會根據實際傳入的 sub class 決定，也就是 shape 物件 x 可以依照其原來的類別進行 draw() 的行為 
    ```cpp
    void paintall(vector<shape *> & container) {
        for each shape object x  in container     
            x->draw(); // X 可能是 box, circle, rectangle
    }
    ```

## Virtual functions
- 任何想要被繼承的 class overridden 的method 都要宣告成 virtual
  - 一個 function 一旦宣告成 virtual，則在繼承的 class 中也是 virtual。但是可以忽略不寫，不過建議要寫
- Polymorphism only works for pointer and reference with function that declared as virtual (多型只對 pointer, reference,以及宣告為 virtual 的function 有效)
- If a class has any method declared as virtual, its destructor should be declared as virtual. (如果一個 class 有任何一個 method 宣告為 virtual 則 destructor 也應該宣告為 virtual ，這為了確保正確的 destructor 做正確的清除  )


### example
這邊舉例 Pet sub class，並有兩個 method
- 因為所有 pet 進行呼吸的方式都一樣，所以這邊的設計不加上 virtual
- 因為不同種 pet 叫的方式不同，所以加上 virtual，這樣未來在實現繼承的時候就能根據實際 sub class 來執行預期的 speak()

```cpp
class Pet {
  public:
    // Constructors, Destructors
    Pet() {}
    virtual ~Pet() {}
    // General methods
    virtual void speak(){};
    void breath(){};
};
```
### Why not declare all methods as virtual?
- 會有額外的 overhead: 
  - The compiler creates a virtual function table that is used in the polymorphism mechanism.
  - Avoiding unnecessary details, the more functions that are declared as virtual, the greater the overhead to create and maintain these tables. 
- But, by declaring all methods virtual, redesign may be avoided if the classes need to change. 

> Some C++ programmers declare all methods virtual if any need be. Some don't. In some programming languages, such as Java, all methods are virtual by default. I don't have a definitive answer on this one.

## Passing arguments
Polymorphism is seen when a pointer or reference of a base class points to a subclass object.

### example 2
> [!IMPORTANT]
>  Methods must be declared as virtual for polymorphism to work.

在 [pet 範例](./pet-virtual/pet.cpp) 中，執行結果會是，可以發現 sub class 物件執行了 base class 的行為

```
Pet Created
Pets singing
Growl
Growl
Growl

Rat Created
Rats singing
Growl
Rat noise
Rat noise

Cat Created
Cats singing
Growl
Meow
Meow
```

## Object Slicing
```c
void chorus(Pet pet, Pet *petPtr, Pet &petRef) {
    pet.speak();
    petPtr->speak();
    petRef.speak();
}
```
- 在 [pet](./pet-virtual/pet.cpp) 的範例中，建立的 Rat、Cat class 物件在執行第一個 `pet.speak();` 執行的是 Pet base class 的行為，是因為在 pass by value 的時候編譯器做了 object slicing，把 sub class 定義的記憶體區塊砍掉了 
  - 原本的 Rat 物件
    ```
    +----------+ 
    |    Pet   | 
    +----------+ 
    |  Rat(x)  |  -> slice later
    +----------+ 
    ```
  - 執行 chorus 函數的時候， Rat 物件會透過 pass by value 的方式傳入成為函數的 Pet pet 參數。為了符合 Pet Class 的大小，所以把 Rat 的部分做 slicing
    ```
    +----------+ 
    |    Pet   | 
    +----------+ 
    ```



### Pass by value
傳入參數到 chorus 的時候會複製一份原先 ptr 的值
```cpp
void chorus(Pet pet) {
    pet.speak();
}

int main() {
  ptr = new Cat;
  chorus(*ptr); // dereference
}
```

### Pass by address
- 沒有複製，把原先物件起始位址傳過去
```cpp
void chorus(Pet *petPtr) {
    petPtr->speak();    // Also (*petPtr).speak(); dereference
}
```

### Pass by reference
- 沒有複製，把原先物件 reference 傳過去
  - 本質上其實也是傳物件起始位址
- 不需要特別做 dereference
> C 沒有
```cpp
void chorus(Pet &petRef) {
    petRef.speak();
}
```

## 物件導向與多型
> 使用多型的用途?

- 方便擴充與維護: 讓核心程式碼的定義和 sub class 型態無關

### example 3: expand our pets

- 以前面的例子，原先的物件定義包含了繼承 Pet 的貓和老鼠，如果後續我多養了其他物種的寵物，在沒有使用 PolyMorphism 的情形下我就要不斷擴充邏輯呼叫不同 sub class 的函數。
  - Why have I chosen an array of pointers of the base class type, "Pet", to store my pets as I enter them into the program. Because I do not know at compile time the type of each subclass object (Rat or Cat) and need to be able to store either. 
  - I need each to behave as the subclass it is. I want polymorphism. That is, I want each object to have the appropriate behavior according to its subclass. 
- 但如果我用多形，Core code 就可以簡化如下，並在擴充 sub class 的時候不需要更動

> Object-oriented programming is about pushing the core parts outward and encapsulating the changing parts, such as future extensions and additions.
```cpp
while() {
    ...
    else {
        cout << "Invalid Choice, Reenter" << endl;
    }
}

Animal* house[10];
totalNumber = i;

for (i = 0; i < totalNumber; i++) {
    house[i]->speak(); // 會自己根據 sub class type 執行對應的 speak
}
```

> An array of objects would not work. Remember, polymorphism is supported through pointers and references. 

#### wrong example

```cpp
int main() {
    Animal house[2];   // object array

    house[0] = Dog();  //  Dog 被 slicing 成 Animal

    house[0].speak();  // output: Animal sound instead of Woof

    return 0;
}
```

### the four basic elements in OOP
> In object-oriented languages, polymorphism is a natural result of combining inheritance and message passing.

- 物件與 message(method)
- Dynamic binding(via polymorphism)
- inheritance
- encapsulation
  - public, protected, private

> Polymorphism refers to the ability of a function to automatically perform different operations and functionalities based on the type or object it is dealing with. Unlike overloading, polymorphism allows the same block of code to be used to operate on different data types or objects.

### example 4: Making PolyMorphism without OOP
以 C 為例，若要實現多型，就得在每一次新增 sub class 的時候維護相關的程式碼 (e.g. 下方 switch case)，但這就造成高耦合
> 物件導向透過 base class interface 降低耦合性

```cpp
Color newColor;     // Currecnt drawing color

void main() {
    int Cont = 1;   // Continue flag
    int Event = 0;  // Event code

    if (Initial()) {    // Enter the drawing mode and other settings
        while (Cont) {
            Event = GetEvent(); // Get the event code
            switch (Event) {    // Determine the event code
                case Circle:
                case Pie:
                case Ellipse:
                case EllipsePie:
                    gCircle(Event, NowColor); // if circle function related, call gCircle function
                    break;
                case Rect:
                case RoundRect:
                case Box:
                    gRect(Event, NowColor); // if rectangle function related, call gRect function
                    break;
                ...

                case Exit:
                    Cont = !gExit();    // if exit function related, call gExit function
                    break;
            }
        End();      // Release memory and exit the drawing mode
        }
    }
}
```



## function pointer
- 指向函數的位址


```cpp
int (*f)(int, int);
int (*f[])(int,int);
```

以剛剛的 example 4，可以用 function pointer 來簡化

```cpp
Color newColor;
int Cont = 1;

void main() {
    int E = 0;
    struct {
        int (*Draw) (void (*)(), void (*)()); // 定義一個函數可以傳入兩個函數的位址、回傳 int
        void (*Move);
        void (*Act);
    } F[] = {
        // 只需要在此擴充
        {gRegion, XorCircle, PutCircle},
        {gRegion, XorCircle, PutPie},
        {gRegion, XorEllipse, PutEllipse},
        {gRegion, XorEllipse, PutEllipsePie},
        {gRegion, XorRect, PutRect},
        {gRegion, XorLine, PutBar},
        {gExit, NULL, NULL}
    };

    // 透過 function pointer，這個 if section 就不需要受到未來變動而改變
    if (Initial()) {
        while (Cont) {
            E = GetEvent();
            (*F[E].Draw)(F[E].Move, F[E].Act);
        }
        End();
    }
}
```


## PolyMorphism 實作原理: Dynamic binding

### What is binding? 
會對應到 logical address

### Static Binding
- processes that occur before a program is run / 在程式執行之前，呼叫端與被呼叫端的關係就已經完全固定。
- 比方說執行以下程式碼後
  ```c
  void do_something() {
      /* */
  }
  void sit_on_it() {
      /* */
  }
  void think_it() {
      /* */
  }

  main() {
      float x, y, z;
      sit_on_it();
      think_it();
      do_something();
      x = y + x;
  }
  ```
- compiler 編譯成的組合語言大致如下
  - 下方範例都是 static binding (在變成執行檔前就完成 addr binding)
    1. Compliation time binding: The compiler resolves names and addresses to fixed locations during the compilation of individual source files.
    2. Linking time binding
      - e.g. `printf`
      - The linker collects and combines various object files and libraries into a single executable file, resolving references between them. This happens after individual source files have been compiled.
  ```asm
      START    MAIN
  do_something:
      ...
      RET
  sit_on_it:  <-----------------+      
      ...                       |
      RET                       |
  think_it:                     |
      ...                       | bind (point to function's logical addr)
      RET                       | (compliation time binding)
                                |
  main:                         |
      ...                       |
      CALL sit_on_it      // <--+
      CALL think_it       
      CALL do_something   
      ...
      PUSH y
      PUSH z
      CALL FLOAT_PLUS   // <-- Conduct the Library (Linking time binding)
      MOVE R0, x
      END
  ```

### Static Linking of External References in C Language
- static linking 是在程式執行前，處理 symbol 與 binary code 的結合。
- Static Linking of External References（外部引用的靜態連結）是編譯器連結器（Linker）在程式執行前，將程式碼中引用的外部函式或變數（External References）
  - e.g. 
    - 當 `main.c` 呼叫了 `actions.c` 裡的 `sit_on_it()` 時，`sit_on_it` 對於 `main.c` 來說就是一個 External Reference（外部引用）。
    - 當程式使用到並非在該檔案定義的 symbol（例如 `printf` 或是另一個檔案中的全域變數）時，編譯器會將其標記為外部引用（External References），
  - 行為：編譯完成的檔案不會變動，因此如果在編譯的時候不知道一些函數的位址，它就會使用 static linking 到一個 table 或一個暫存器，也就是下方 `ExtTbl` 位置。
```
                      Compile Action         
                      --------------        

                    Compiled Assembly Code 
                    +-------------------+  
                    | main:             |  
                    |   CALL ExtTbl[0]; |
Original Code       |   sit_on_it;      |
Without define  ->  |                   |
these finctions     |   CALL ExtTbl[1]; |
                    |   think_it;       |
                    |                   |
                    |   CALL ExtTbl[2]; |
                    |   do_something;   |
                    +-------------------+
                      (Indirect CALL)
```
#### 實驗
- static linking 引用外部檔案
  - 實際實驗: [這裡(多個目標檔（.o）結合成一個執行檔的過程)](./Linking_Time_Binding/README.md)
- dynamic linking 引用 `.ddl` 或 `.so`
  - 會在作業系統執行程式的時候才由作業系統去根據執行檔的內容去抓特定 DLL、並放到記憶體區塊 -> 我們不會預先知道 DLL 的位址 -> 等到 DLL 載入後得知對應函數 logial addr，再把這些 addr 寫入 External Reference Table
  - 實際實驗: [這裡(引入外部 `.so` )](./dynamic_linking/README.md)

```
                      Compile Action                                Linking Action 
                      --------------                                --------------

                    Compiled Assembly Code     External Reference Table         External Goal File
                    +-------------------+    +---------------------+-----+    +--------------------+ 
                    | main:             |    |                     |     |    |                    | 
                    |   CALL ExtTbl[0]; |----|---->  sit_on_it;    |  <--|----|----> sit_on_it;    |        
Original Code       |   sit_on_it;      |    |                     |     |    |     ...            |    
Without define  ->  |                   |    |                     |     |    |     RET            |     
these finctions     |   CALL ExtTbl[1]; |----|---->  think_it;     |  <--|----|----> think_it;     |       
                    |   think_it;       |    |                     |     |    |     ...            |      
                    |                   |    |                     |     |    |     RET            |     
                    |   CALL ExtTbl[2]; |----|----> do_something;  |  <--|----|----> do_something  |      
                    |   do_something;   |    |                     |     |    |   ...              |  
                    +-------------------+    +---------------------+-----+    +--------------------+
                      (Indirect CALL)                                                  (DLL)
```

#### Indirect call 間接呼叫
- Indirect Call 是指在執行程式時，目標函式的位址並非直接寫死在指令中，而是透過暫存器或記憶體中的指標（Pointer）來跳轉。 
- 以上面的例子來說，編譯完成的檔案會呼叫 `ExtTbl[0];`，接著 `ExtTbl[0];` 會取出 table 索引值 0 的值，也就是 DLL 中目標函數的 logical addr


### Dynamic Binding
- 直到程式跑到了那一行(runtime)，才根據當下物件的「型別」或「指標內容」決定要執行哪段程式碼。
- 它的原理就是 Indirect call
- 範例：
  - C++ 的虛擬函式 (Virtual Functions)：透過 Vtable 查表。

> [!important]
> Dynamic Binding（動態綁定/遲綁定）與 Dynamic Linking（動態連結）的主要差異在於解決的問題不同：Dynamic Binding 決定「執行哪個方法」（多型），在執行期根據物件類型判斷；Dynamic Linking 決定「使用哪個外部函式庫」，在程式執行時才載入 DLL 或 .so 檔案。

### Virtual Function with Dynamic Binding 
- 只要宣告 virtual function，就會建立 vtable
- 一個 class 只會有一個 virtual table，這個 class 建立的物件會共用這個 virtual table


#### base class
```cpp
class Shape {
public:
    double x0, y0;
    Shape(double x, doubel y);
    virtual double area();
    virtual void   draw();
}
```
```
Shape Table   +----->  Virtual Function Table    Practical Function
+----------+  |       +---------------------+   +-----------------+
| x0, y0   |  |       | (*area)()   --------|---|-> Shape::area() |
+----------+  |       +---------------------+   +-----------------+
| vptr; ---|--|       | (*draw)()   --------|---|-> Shape::draw() |
+----------+          +---------------------+   +-----------------+
```
#### Derived Classes
```cpp
class Circle : Public Shape {
    public:
        double radius;
        Circle(double x, double y, double r);
        void draw(); // override
        // area() no override -> use Shape::area()
}
```
```
Shape Table   +----->  Virtual Function Table    Practical Function
+----------+  |       +---------------------+   +------------------+
| x0, y0   |  |       | (*area)()   --------|---|-> Shape::area()  |
+----------+  |       +---------------------+   +------------------+
| vptr; ---|--|       | (*draw)()   --------|---|-> Circle::draw() |  (特異化)
+----------+          +---------------------+   +------------------+
| radius   |  
+----------+  
```


```cpp
Shape *p ;
Shape A ;
Circle B ;

p = &A ;
p->draw();      // (p->vptr[1])();  Shape object
p = &B ;
p->draw();      // (p->vptr[1])();  Circle object
```
多型的原理是讓指標 p 依據它所指向物件的 virtual table，找到對應的函式來執行。以上面的例子來說就是
- `p = &B ;`
  ```
          Shape Table   +----->  Virtual Function Table    Practical Function
  p ----> +----------+  |       +---------------------+   +------------------+
          | x0, y0   |  |       | (*area)()   --------|---|-> Shape::area()  |
          +----------+  |       +---------------------+   +------------------+
          | vptr; ---|--|       | (*draw)()   --------|---|-> Circle::draw() |
          +----------+          +---------------------+   +------------------+
          | radius   |  
          +----------+  
  ```

> [!Note]
> 為何會說它的原理是 indirect call?
> 因為編譯器只會把 `p->draw();` 編譯成 `(p->vptr[1])();`，他只有在後續執行的時候才會去抓&執行 `vptr[1]` 的內容


## OO: planning and design first, then programming
Actually, writing OO programs is a process, not just programming. Most programmers learn OOP (C++, Java) first, without knowing that writing OO programs require a planning and design first.

It is a process not a programming task! It's goal: to make the system highly reusable and maintainable
```cpp
class Circle : Public Shape{
    public:
        virtual void Draw() { ... }
        virtual void  Move() { ... }
        virtual void  Act() { ... }
};
void main () {
    Vector <Shape *>  ShapePool ;
    ShapePool.insert(new Circle);
    ShapePool.insert(new Pie);
    ...
    if (initial()) {
        while (cont) {
            E = GetEvent();
            ShapePool[E]->Draw();   // How can this be achieved?
        }
    }
}
```

Take the following examples again. When you want to extend the system to another shape called Polyghon. You simply write a class to extend Shap and add a new line in `main()` or some function called init() and then you do not need to change other parts of the program.



## Virtual Base Class (Abstract class)
若 class 中的 member functions 是 pure virtual function，則稱為 Virtual Base Class (Abstract class)

```cpp
virtual void p() = 0 ;
```
These classes are called abstract classes, which means they cannot be instantiated. In other words, you cannot create instances of these classes using the `new` keyword in your program. If you try to do so, you will encounter a compile error.

```cpp
class Human {
      public:
          virtual Money work() = 0 ;
};
```

### Thumb rules
- 假設某個member function 以後有可能會被derived class修改，就在他的前面加 virtual 就對了。
- 假如你喜歡用多重繼承，那麼只要這個class可能有兩個以上的 derived class 則你應該在繼承他的時候在前面加上 virtual


### Question
Why not making an abstract class to have all the methods to be abstract and enforce its subclasses to implement each methods? Such as 

```cpp
class Human {
      public:
         virtual void walk() = 0 ;
         virtual void breath() = 0 ;
         virtual void speak()=0;
};
```

Making all methods abstract in a base class forces every subclass to implement them, which ensures consistency but can also lead to unnecessary duplication.

In practice, we often want the base class to preserve the fundamental behavior or shared concept, so that the core logic remains stable and does not need to be reimplemented in every subclass. Subclasses can then extend or customize specific parts based on this shared foundation, enabling polymorphism in a more flexible and maintainable way.

