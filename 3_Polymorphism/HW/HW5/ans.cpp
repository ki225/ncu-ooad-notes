#include <stdio.h>
#include <assert.h>

#define SIZE 3

class Book {
public:
    virtual void print_book_type() = 0;
    Book () {}
    ~Book () {}
};

class Comic : public Book {
public:
    virtual void print_book_type() {printf("Comic\n");}
    Comic () {}
    ~Comic () {}
};

class Noval : public Book {
public:
    virtual void print_book_type() {printf("Noval\n");}
    Noval () {}
    ~Noval () {}
};

class Magazine : public Book {
public:
    virtual void print_book_type() {printf("Magazine\n");}
    Magazine () {}
    ~Magazine () {}
};

int main(void) {
    Book* books[3] = {new Comic(), new Noval(), new Magazine()};

    for (int i = 0; i < SIZE; i++) {
        books[i]->print_book_type();
    }

    return 0;
}
