#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee {
  public:
    Employee(char *name, int id);
    ~Employee();
    char *getName();
    int getId();
    // Other Accessor methods
  private:
    int _id;
    char *_name;
};

#endif /* EMPLOYEE_H */