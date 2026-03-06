#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee {
  public:
    Employee(char *name, int id);
    // self-defined copy constructor
    Employee(Employee &rhs); // right hand side
    ~Employee();
    char *getName();
    int getId();
    // Other Accessor methods
  private:
    int _id;
    char *_name;
};

#endif /* EMPLOYEE_H */