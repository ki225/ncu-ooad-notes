# Comparison of C++ and Java

## Pass parameters to base class

In C++, we can use a member initialization list to initialize base class parameters before creating a subclass object. In contrast, Java uses `super()` to call the parent constructor. In Java, `super()` must be the first statement in the constructor.

### C++

```cpp
class Pet {
  public:
    // Constructors, Destructors
    Pet() : weight(1), food("Pet Chow") {}
    Pet(int w) : weight(w), food("Pet Chow") {}
    Pet(int w, string f) : weight(w), food(f) {}
    ~Pet() {}
};
class Rat : public Pet {
  public:
    Rat() {}
    Rat(int w) : Pet(w) {}
    Rat(int w, string f) : Pet(w, f) {}
    ~Rat() {}
};
```

### Java

```java
class Pet {
    // Constructors
    Pet () {}
    Pet(int w) {}
    Pet(int w, string f) {}
}

class Rat extends Pet {
    Rat() {}

    Rat(int w) {
        super(w);  // parent class constructor
        ...
    }

    Rat(int w, string f) {
        super(w, f);
        ...
    }
}
```


## Array

When defining an array of class types in C++, 100 objects are created and memory is allocated immediately. The constructor is called 100 times.

However, in Java, defining an array of a class type only creates references. No actual objects are allocated until explicitly instantiated.

### C++

```cpp
class Pet {
};
Usage:

Pet allpets[100];  // declares 100 objects, memory is allocated, constructors are called 100 times
```

### Java

```java
class Pet {
}
Usage:

Pet allpets[100];  // declares 100 references, no objects are allocated

// objects must be explicitly created
for (int i = 0; i < 100; i++) {
    allpets[i] = new Pet();
}
```

## Parameter Passing to methods

### C++

* For both primitive types and class types, parameters can be passed by:
  * value
  * address (pointer)
  * reference

### Java

* Primitive types (`int`, `char`, `float`, `double`, etc.)
  * Passed by value only
* Class types (objects)
  * Passed by value of the reference (often described as “reference-like behavior”)

For example, the following code allocates 4 bytes for variable `x` since `int` is a primitive type:

```java
int x;
```

But the following only creates a reference:

```java
class P {...}

P x;
```


### Think: compare `swap(a, b)` in C++ and Java

In C++, we can choose pass-by-value or pass-by-reference depending on the function signature:

```cpp
// pass by value
// this will NOT actually swap the original variables,
// because only copies of the values are modified
void swap(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

// pass by reference
// this will swap the original variables
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}
```

In Java, everything is strictly pass-by-value. Swapping two primitive variables will not work:

```java
public class SwapPrimitivesTypeVar {
    public static void main(String[] args) {
        int a = 10;
        int b = 20;
        swap(a, b);
        System.out.println("a = " + a + ", b = " + b); // Not swapped
    }

    public static void swap(int a, int b) {
        int temp = a;
        a = b;
        b = temp;
    }
}
```

The solution is to use a mutable wrapper class, since object references are passed by value but still refer to the same object:

```java
class IntClass {
    int value;
    IntClass(int value) {
        this.value = value;
    }
}

public class Swap {
    public static void main(String[] args) {
        IntClass a = new IntClass(10);
        IntClass b = new IntClass(20);
        swap(a, b);
        System.out.println("a = " + a.value + ", b = " + b.value); 
    }

    public static void swap(IntClass a, IntClass b) {
        int temp = a.value;
        a.value = b.value;
        b.value = temp;
    }
}
```
```sh
javac Swap.java
java Swap
```

More information can be discussed in this [post](https://aditya45.medium.com/why-java-fails-to-swap-understanding-pass-by-value-and-immutable-integer-13b3e1dff5ec)


## Object allocation

* C++ (for primitive types or class types)
  * Global variables (data segment)
  * Local variables (stack)
  * Heap variables
* Java
  * Global variables: approximated via `static` inside a class
  * Local variables: only for primitive types
  * Heap variables: for all objects (and arrays)



## Abstract class

### C++

```cpp
class Human {
    int weight;
    int height;
public:
    virtual void walk() = 0;
    virtual void speak() = 0;
};
```

### Java

The following example can also be written as `public class Human {...}` because a class becomes abstract automatically if it contains at least one abstract method.

```java
public abstract class Human {
    int weight;
    int height;

    public abstract void walk();
    public abstract void speak();
}
```


## Inheritance

### C++

* Pass parameters from subclass to base class constructor using a member initialization list

### Java

In a constructor, if `super()` is used, it must be the very first statement. You cannot access `this.xxx` variables or methods before calling `super()`.

However, if you want to call a parent class method instead of an overridden method, you can use `super.method()`.

```java
// using super in a constructor
public MyClass(Thing thing, Color color) {
    super(thing);  // call parent constructor
    this.color = color;
}

// using super in a method
public void myMethod(Font font) {
    super.myMethod(font);   // call parent version
    super.otherMethod(font);
}
```

---

If you want, I can next help you **upgrade this into interview-ready notes** (more precise wording + fewer “grey area” statements like Java reference passing).
