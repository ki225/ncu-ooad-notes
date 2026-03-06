## Usage of Object array

```cpp
#include <iostream>
#include <string>

using namespace std;

class Cat {
public:
    Cat(string name = "tom", string color = "black_and_white") : _name(name), _color(color) {

    }
    ~Cat() {}
    
    void setName(string name) {
        _name = name;
    }

    string getName() {
        return _name;
    }
    
    void setColor(string color) {
        _color = color;
    }
    
    string getColor() {
        return _color;
    }
    
    void speak() {
        cout << "meow" << endl;
    }
private:
    string _name;
    string _color;
};
```

建構子 (constructor) 參數與程式中間的 `_name(name), _color(color)` 是在取得參數、執行 `{}` 程式之前所執行的內容，他的意思其實等同於
```cpp
Cat(string name = "tom", string color = "black_and_white") {
    _name = name;
    _color = color;
}
```

## Rule of Three
destructor

copy constructor

copy assignment operator