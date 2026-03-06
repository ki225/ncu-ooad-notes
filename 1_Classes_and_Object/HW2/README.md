```cpp
#include 

class Bar {
private:
    std::array not_important_;
};

class Foo {
public:
    // constructor
    Foo() : bar_{new Bar{}} {}

    // copy constructor
    // 完成 deep copy
    Foo(const Foo& rhs) {
        bar_ = new Bar(*rhs.bar_);
    }

    // operator overloading
    Foo&
    operator=(const Foo& rhs) {
        // copy member, ref: F.47: Return T& from assignment operators
        Foo temp(rhs);              // 先 copy (可能丟 exception)
        std::swap(bar_, temp.bar_); // swap, C++ 確保 swap 不會 exception
        return *this;
    }

    // destructor
    ~Foo() {
        delete bar_;
    }

private:
    // XXX: Well, this is not doing well in practical...
    // but hey, this is just some exercise. Please use
    // std::unique_ptr or std::shared_ptr instead.
    //
    // The Foo object will "own" this Bar pointer.
    Bar* bar_{nullptr};
};
```