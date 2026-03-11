## Q
In C++, Kevin wrote the following code first
```c
Class A {
   A() ;
   protected:
     int foo ;
};
Class B : A {
   B() ;
   protected:
     string bar ;
};
```
In main(), Kevin feel the need to initialize foo when needed
That is, he needs to declare a variable like 
```c
B b(100); // where 100 is to initialize foo. 
```
Please modify the code the above to help Kevin.