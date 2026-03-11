#include <iostream>
#include <cstddef>
#include <iomanip>
using namespace std;


class pet {
public:
    int p = 2; 
    char c ='a';
    ~pet(){ cout << "delete pet" << endl; }
    void speak(){}
};


class cat : public pet {
public:
    int a = 4;
    ~cat(){ cout << "delete cat" << endl; }
};

void dumpMemory(unsigned char* mem, size_t size)
{
    for(size_t i=0;i<size;i++)
    {
        cout<<hex<<setw(2)<<setfill('0')<<(int)mem[i]<<" ";
        if((i+1)%8==0) cout<<endl;
    }
    cout<<endl;
}

int main() {
    // sizeof(pet) 8
    // sizeof(cat) 12
    cout<<"sizeof(pet) "<<sizeof(pet)<<endl;
    cout<<"sizeof(cat) "<<sizeof(cat)<<endl;

    cout<<"offset of pet::p "<<offsetof(pet,p)<<endl;
    cout<<"offset of pet::c "<<offsetof(pet,c)<<endl;
    cout<<"offset of cat::a "<<offsetof(cat,a)<<endl;


    // see Polymorphism
    pet* nose = new cat();

    cout<<"object address "<<nose<<endl;

    unsigned char* obj = (unsigned char*)nose;

    // 往前看 metadata
    unsigned char* meta = obj - 32;

    cout<<"\n==== MEMORY BEFORE DELETE ====\n";

    /*
    [metadata area]
    00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00
    21 00 00 00 00 00 00 00 ---> chunk size (0x21 = 0x20 bytes + PREV_INUSE flag)
    */
    cout<<"\n[metadata area]\n";
    dumpMemory(meta,32);

    /*
    Memory BEFORE delete:
    02 00 00 00 61 00 00 00
    04 00 00 00
    */
    cout<<"\n[object area]\n";
    dumpMemory(obj,sizeof(cat));


    cout<<"\n--- delete object ---\n";

    delete nose;

    /*
    3e 75 35 5a 05 00 00 00
    38 fd e5 26
    */
    cout<<"\nMemory AFTER delete:\n";
    dumpMemory(obj,sizeof(cat));

}