# Chapter 2.6 - Why you should not abuse inheritance over composition
> 繼承不能被濫用

## 情境
### Inheritance
```cpp
class EmployeeCensus : public vector {

    // public routine
    void addEmployee(Employee employee);
    void removeEmployee(Employee employee);

    Employee NextItemList();
    Employee FirstItem();
    Employee LastItem();
}
```

### Composition
```cpp
class EmployeeCensus {

    // employeecensus number data

    vector Employees;

    // public routine
    void addEmployee(Employee employee);
    void removeEmployee(Employee employee);

    Employee NextItemList();
    Employee FirstItem() {
        return employees.front();
    }
    Employee LastItem();
}
```

## problem

### override
- 以下方例子而言，因為他繼承了 `vector` type，所以他可以使用 `vector` 底下的所有 methods，因此 EmployeeCensus class 是可以寫一個 vector 擁有的 method 來 override 掉 vector 的 method。
- 這樣的可能性讓我們可能會因為不注意而在無意間更改了一些 method 的操作行為。
```cpp
class EmployeeCensus : public vector {

    // public routine
    void addEmployee(Employee employee);
    void removeEmployee(Employee employee);

    Employee NextItemList();
    Employee FirstItem();
    Employee LastItem();
}
```
> 當然除了 override 之外，在處理繼承的時候也要確保 A class only carry the methods needed !!

### Polymorphism Freedom
延續上面的例子，因為 EmployeeCensus 繼承了 Vector，所以 EmployeeCensus 建立的物件是可以被轉成 Vector 型態實現 Polymorphism，但這通常不是我們想要的用意，應該避免非預期操作的可能性。
```cpp
Vector *v = new EmployeeCensus(); 
```

### Copy-paste programming
下面的範例會看到有多個重複的 methods，這種繼承會造成 Copy-paste programming
```c
class myGreatTransmitterTCP : tcp {
    void send(string d) { 
      // done by TCP
    }
    void doSomething1(......);
    void doSomething2(......);
}

// If still more protocol
class myGreatTransmitterRS232 : RS232 {
    void send(string d) { 
      // done by RS232
    }
    void doSomething1(......);
    void doSomething2(......);
}

class myGreatTransmitterUSB : USB {
    void send(string d) { 
      // done by USB
    }
    void doSomething1(......);
    void doSomething2(......);
}
```
好的寫法應該是
```cpp
class myReallyGreatTransmitter {
    protocol m;
    myReallyGreatTransmitter(protocol m);
}

myGreatTransmitterTCP = new myReallyGreatTransmitter(new tcp);
myGreatTransmitterRS232 = new myReallyGreatTransmitter(new rs232);
myGreatTransmitterUSB = new myReallyGreatTransmitter(new USB);
```