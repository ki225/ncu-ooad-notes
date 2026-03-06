#include <iostream>
using namespace std;

// Employee class
class Employee {
public:
  Employee(char *name, int id);
  Employee(Employee &rhs);
  ~Employee();
  char *getName(){return _name;}
  int getId() {return _id;}
  //Other Accessor methods
private:
  int _id;
  char *_name;
};

Employee::Employee(char *name, int id){
  _id = id;
  _name = new char[strlen(name) + 1]; 
  //Allocates an character array object
  strcpy(_name, name);
}

Employee::~Employee(){
  delete[] _name;
}

Employee::Employee(Employee &rhs){
  _id = rhs.getId();
  _name = new char[strlen(rhs.getName()) + 1];
  strcpy(_name,rhs._name);
} 

int main(){
  Employee programmer("John",22);
  cout << programmer.getName() << endl;
  //Lots of code ....
  Employee manager = programmer; 
  
  //Creates a new Employee "manager",
  //which is an exact copy of the 
  //Employee "programmer".

  delete programmer ;
  return 0;
} 
