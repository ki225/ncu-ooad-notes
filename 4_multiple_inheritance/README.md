# Multiple Inheritance

## Background

```cpp
class Vehicle {
  public:
    Vehicle() { cout << "Vehicle Constructor" << endl; }
    virtual ~Vehicle() { cout << "Vehicle Destructor" << endl; }
    virtual void accelerate() const { cout << "Vehicle Accelerating" << endl; }
    void setAcceleration(double a) { acceleration = a; } // no virtual: tell developer not to override it, just inherit
    double getAcceleration() const { return acceleration; }

  private:
    double acceleration;
};

class Car : public Vehicle {
  public:
    Car() { cout << "Car Constructor" << endl; }
    virtual ~Car() { cout << "Car Destructor" << endl; }
    virtual void accelerate() const { cout << "Car Accelerating" << endl; }
    void drive() const { cout << "Car Driving" << endl; }

  private:
    // Car inherits acceleration accessors, member
};

int main() {
    Car myCar;
    myCar.setAcceleration(9.81);
    cout << "Accelerating at " << myCar.getAcceleration() << " m/(s*s)";
    cout << endl;

    myCar.accelerate();
    myCar.drive();
}
```

- Accelerate method is declared as virtual. Any method that will be overridden in a subclass should be declared as virtual. 
- Notice that in the Car class I have used the keyword virtual as a specifier on the Accelerate method. This is optional. Once a method is declared as virtual, it is automatically virtual in all subclasses. But, by using the keyword "virtual" in Car, it is clearer that `Accelerate()` is a virtual method. Another programmer, looking only at the Car class, would know that the method was virtual.
- `setAcceleration` and `getAcceleration`, are non virtual. Why? 
  - I don't expect to override them in any subclasses, but rather just inherit them. Notice that the Car class has indeed inherited these methods. 

```cpp
class JetCar : public Car {
    public:
        JetCar() {}
        virtual ~JetCar() {}
        virtual void drive() const { cout << "JetCar driving" << endl; }
        virtual void fly() const { cout << "JetCar flying" << endl; }
};

/*
-----------------------
some function elsewhere
-----------------------
*/

void analyzePerformance(Car *testVehicle) {
    testVehicle->drive();
    testVehicle->fly();
}
```
- the `drive()` method of JetCar override the the `drive()` of car because the driving method of jetcar should be a little different from car
- because JetCar can fly, so a new method called `fly()` is added and is prepared to be overridden
  - However, since `fly()` is not defined in the base class Car, the following compilation error occurs:
    ```
    Car_vehicle.cpp: In function ‘void analyzePerformance(Car*)’:
    Car_vehicle.cpp:44:18: error: ‘class Car’ has no member named ‘fly’
    44 |     testVehicle->fly();
       |                  ^~~
    ```

### Percolating upward

To resolve the issue above, one of the possible approach is percolating up.
- Percolating up means moving behavior defined in a derived class up into its base class.
- In this example, we can define `fly()` in the Car class to eliminate the compilation error.

```cpp
class Car : public Vehicle {
  public:
    Car() {}
    virtual ~Car() {}
    virtual void accelerate() const { cout << "Car Accelerating" << endl; }
    virtual void drive() const { cout << "Car Driving" << endl; }
    virtual void fly() const { cout << "Cars can only fall" << endl; }

  private:
    // Car inherits acceleration accessors, member
};

class JetCar : public Car {
  public:
    JetCar() {}
    virtual ~JetCar() {}
    virtual void drive() const { cout << "JetCar driving" << endl; }
    virtual void fly() const { cout << "JetCar flying" << endl; }
};

int main() {
    Car myCar;
    JetCar myJetCar;
    analyzePerformance(&myCar);
    analyzePerformance(&myJetCar);
    return 0;
}
```
> [!IMPORTANT]
> Percolating up is generally not a good design choice.
> Object-Oriented Programming should reflect real-world concepts. In this case, a Car should not have a `fly()` behavior, as cars do not fly.

If we percolated up more methods as we built these classes, Car becomes bloated and confused. Generally, only functionality common to all subclasses belongs in a base class.

### Casting down

Another solution is casting down.

```cpp
class Car : public Vehicle {
  public:
    Car() {}
    virtual ~Car() {}
    virtual void accelerate() const { cout << "Car Accelerating" << endl; }
    virtual void drive() const { cout << "Car Driving" << endl; }

  private:
    // Car inherits acceleration accessors, member
};
class JetCar : public Car {
  public:
    JetCar() {}
    virtual ~JetCar() {}
    virtual void drive() const { cout << "JetCar driving" << endl; }
    virtual void fly() const { cout << "JetCar flying" << endl; }
};

void analyzePerformance(Car *testVehicle) {
    JetCar *ptr;
    // A pointer of subclass type, JetCar
    testVehicle->drive();
    // drive() exists for both base and sub class
    ptr = dynamic_cast<JetCar *>(testVehicle);      // cast down to JetCar pointer
    if (ptr) {
        ptr->fly();
    } else {
        cout << "Car being tested" << endl;
    }
}

int main() {
    Car myCar;
    JetCar myJetCar;
    analyzePerformance(&myCar);
    analyzePerformance(&myJetCar);
    return 0;
}
```
This approach is called casting down, because we convert a base class pointer (`Car*`) into a derived class pointer (`JetCar*`).

```cpp
JetCar *ptr = dynamic_cast<JetCar *>(testVehicle);
```

#### RTTI (Runtime Type Identification)
- C++ has a built in mechanism for Runtime Type Identification, RTTI. This means that as a program is running it is possible to determine the exact type of object a pointer or reference refers to. 
- RTTI is achieved in C++ via the dynamic_cast operator, the typeid operator and the type_info class. 
- The dynamic_cast operator returns a pointer to type JetCar if have the address of a JetCar object in the original pointer, testVehicle. Otherwise, the dynamic_cast operator returns NULL. 
  - If testVehicle is a JetCar, the cast succeeds and returns its address
- Dynamic casting used in this manner is referred to as "casting down". We have casted a base class pointer down its hierarchy into a subclass pointer. 

#### Drawback
We use casting down to determine the actual type of testVehicle, but this approach is generally not ideal. As more subclasses are added (e.g., SubmarineCar, FlyingCar, etc.), we must continuously extend this logic with additional type checks.
```cpp
void analyzePerformance(Car *testVehicle) {
    JetCar *ptr;
    testVehicle->drive();
    ptr = dynamic_cast<JetCar *>(testVehicle);

    // The logic must grow as more subclasses are introduced
    
    if (ptr) {
        ptr->fly();
    } else {
        cout << "Car being tested" << endl;
    }
}
```

#### Casting down in Java - `instanceof`

```java
analyzePerformace (Car testvehicle) {
    if (testvehicle instanceof JetCar) {
        ...
    }
}
```

#### Casting up
When implementing polymorphism, we are essentially performing casting up, since we assign a derived class object to a base class pointer.

```cpp
Car *pt = (Car*)new JetCar;
```

### Casting in C and C++

```cpp
ptr = dynamic_cast <JetCar *>(testVehicle); // Dynamic Cast
ptr = static_cast <JetCar *>(testVehicle); // Static Cast 
ptr = (JetCar *) testVehicle; // C style static cast
```

In Visual C++, RTTI is not turned on by default, if you run this code without turning on RTTI, you will get a cryptic error message saying something like "'dynamic_cast' used on polymorphic type 'Car' with /GR-; unpredictable behavior may result". Turning on RTTI allows the compiler to insert additional code to support RTTI as it forms object files.

## Multiple Inheritance

Since JetCar conceptually has both `Jet` and `Car` characteristics,
a better design is to model them separately and let `JetCar` inherit from both:
- Define:
  - `Car` → driving behavior
  - `Jet` → flying behavior
- Then:
```cpp
class JetCar : public Car, public Jet {
    // combine both capabilities
};
```

### Correct

```cpp
#include <iostream>

using namespace std;

class Vehicle {
  public:
    Vehicle() { cout << "Vehicle Constructor" << endl; }
    virtual ~Vehicle() { cout << "Vehicle Destructor" << endl; }
    virtual void accelerate() const { cout << "Vehicle Accelerating" << endl; }
    void setAcceleration(double a) { acceleration = a; }
    double getAcceleration() const { return acceleration; }

  protected:
    double acceleration;
};

class Car : public Vehicle {
  public:
    Car() { cout << "Car Constructor" << endl; }
    virtual ~Car() { cout << "Car Destructor" << endl; }
    virtual void accelerate() const { cout << "Car Accelerating" << endl; }
    virtual void drive() const { cout << "Car Driving" << endl; }

  private:
    // Car inherits acceleration accessors, member
};
class Jet : public Vehicle {
  public:
    Jet() { cout << "Jet Constructor" << endl; }
    virtual ~Jet() { cout << "Jet Destructor" << endl; }
    virtual void fly() const { cout << "Jet flying" << endl; }
};

class JetCar : public Car, public Jet {
  public:
    JetCar() { cout << "JetCar Constructor" << endl; }
    virtual ~JetCar() { cout << "JetCar Destructor" << endl; }
    virtual void drive() const { cout << "JetCar driving" << endl; }
    virtual void fly() const { cout << "JetCar flying" << endl; }
};
void analyzeCarPerformance(Car *testVehicle) {
    testVehicle->drive();
    // drive() exists for both base and sub class
}
void analyzeJetPerformance(Jet *testVehicle) {
    testVehicle->fly();
    // fly() exists for both base and sub class
}

int main() {
    Car myCar;
    Jet myJet;
    JetCar myJetCar;

    cout << endl;
    cout << "Car testing in progress" << endl;
    analyzeCarPerformance(&myCar);
    analyzeCarPerformance(&myJetCar);
    cout << "Jet testing in progress" << endl;
    analyzeJetPerformance(&myJet);
    analyzeJetPerformance(&myJetCar);
    cout << endl;

    return 0;
}
```

The inheritance relationship in this example forms a multiple inheritance hierarchy:

```
+----------+     +----------+
|          |     |          |
|  Vehicle |     |  Vehicle |
|          |     |          |
+----------+     +----------+
    |                  |
    |                  |
+-------+          +-------+
|       |          |       |
|  Car  |          |  Jet  |
|       |          |       |
+-------+          +-------+
         \        /
          \      /
        +----------+
        |          |
        |  JetCar  |
        |          |
        +----------+

```


- JetCar inherits from both Car and Jet.
- JetCar inherits two Vehicle parts. This means that when calling a method that is in Vehicle, but not overridden in the subclass JetCar, or when we access a variable that exists only in Vehicle,

A JetCar object is defined as:

```cpp
class JetCar : public Car, public Jet {
    // combine both capabilities
};
```
Its memory layout conceptually looks like:
```
+---------+
| Vehicle |  
+---------+     
|   Car   |   
+---------+
| Vehicle |  
+---------+
|   Jet   | 
+---------+  
```
Because both Car and Jet inherit from Vehicle,
a JetCar object contains two separate Vehicle subobjects:
- one through Car
- one through Jet

## ambiguity

Ambiguity can happen when you use multiple inheritance
```cpp
JetCar myJetCar;
myJetCar.setAcceleration(10);  // ambiguous!
```

The compiler does not know which Vehicle to use:
- the one inherited via Car
- or the one inherited via Jet

This results in a compilation error due to ambiguity.

> [!IMPORTANT]
> we must explicit specify which Vehicle part we are accessing: we must explicit specify which Vehicle part we are accessing:

### Solution 1 – casting ambiguous attributes or methods
```cpp
class task {
    // ...
    virtual debug_info *get_debug();
};
class Displayed {
    // ...
    virtual debug_info *get_debug();
};
class Satellite : public task, public displayed {
    // ...
};
void print_debugging(Satellite *sp) {

    debug_info *dip = sp->get_debug();              // wrong
    debug_info *dip = sp->Task::get_debug();
    debug_info *dip = sp->Displayed : get_debug();
}
```

### Solution 2: Overwriting Ambiguous Attributes or Methods
```cpp
class Satellite : public Task, public Displayed {
    // ...

    // write a new function to merge the debugging messages from two sources
    debuLinfo *get_debug() {
        debug_info *dip1 = Task::get_debug();
        debug_info *dip2 = Displayed::get_debug();
        return dip->merge(dip2);
    };
};
```

### Another Case: Link

```cpp
class Link {
    Link * next ;
};
class Task: public Link {
     // using link to maintain a list of tasks
};
class Displayed: public Link {
     // use link to maintain a list of displayed object
};

void mess_with_links(Satellite *p) {
    p->next = 0;                  // wrong
    p->Link::next;                // wrong
    p->Task::Link::next = 0;      // OK
    p->Displayed::Link::next = 0; // OK
}
```

### Another Case: Storable

Storable represents an abstract interface for reading from and writing to a file.

However, in the following example, a Radio object will write to the file twice (duplicate operations).
This happens because both of its base classes share the same parent class.

```cpp
class Storable {
  public:
    virtual const char *get_file() = 0;
    virtual void read() = 0;
    virtual void write() = 0;
    virtual ~Storable(){};
};
class Transmitter : public Storable {
  public:
    void write();
    // ...
};
class Receiver : public Storable {
  public:
    void write();
    // ...
};
class Radio : public Transmitter,
              public Receiver {
  public:
    const char *get_file();
    void read();
    void write();
    // ...
};

void Radio ::write() {
    Transmitter::write();
    Receiver::write();
    // begin to write something that is really related to radio
}
```

## Diamond-Shaped Inheritance
public virtual inheritance
```cpp
class transmitter : public virtual Storable {
  public:
    void write();
};
class Receiver::public virtual Storable {
  public:
    void write();
};
class Radio : public Transmitter, public Receiver {
  public:
    void write();
};
```

```
                +----------+
                |          |
                | Storable |
                |          |
                +----------+
                /      \
                /        \
+-------------+          +-----------+
|             |          |           |
| Transmitter |          |  Receiver |
|             |          |           |
+-------------+          +-----------+
                \        /
                \      /
                +----------+
                |          |
                |  Radio   |
                |          |
                +----------+

```

### Java Interface
