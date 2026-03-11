The following code is Java. There are some compilation errors in the code.
How can you fix it to pass compilation?
You can only change the code without deleting any lines of the code. 

```java
class SuperMan{
    private int a;
    protected SuperMan(int a){this.a = a;}
}
...
class SubMan extends SuperMan{
    public SubMan(int a){super(a);}
    public SubMan(){this.a = 5;}
} 
```
---

## note
- 你會看到題目的錯誤顯示 `The field SuperMan.a is not visible`。
- 因為 `SubMan` class `SubMan(){this.a = 5;}` 存取的 a 在 `SuperMan` class 是 private 屬性，所以任何不在 `SuperMan` class scope 都無法存取。
- `super()` 是呼叫父類別的 constructor

## My ans 1
```Java
class SuperMan{
    private int a;
    protected SuperMan(int a){this.a = a;}
}
...
class SubMan extends SuperMan{
    public SubMan(int a){super(a);}
    public SubMan(){super(5)}
} 
```

## My ans 2
把 `a` 從 private 改成 public 或 protected 讓 `SubMan` 存取，但記得要新增一個沒接收任何參數的 constructor，因為 `public SubMan(){this.a = 5;}` 是呼叫 `SuperMan()` constructor
```Java
class SuperMan{
    protected int a;
    protected SuperMan(int a){this.a = a;}
    protected SuperMan(){}
}
...
class SubMan extends SuperMan{
    public SubMan(int a){super(a);}
    public SubMan(){this.a = 5;}
} 
```

### Test

- env: Ubuntu 24/04
- installing java
  - `sudo apt update`
  - `sudo apt install openjdk-21-jdk`
  - check
    ```
    java -version
    javac -version
    ```
- compile: `javac ans.java`
- execute: `java ans`