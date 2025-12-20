typedef struct {
    // User defined data may be declared here.
    _Atomic(int) flag;
} Foo;

// Function Declaration, do not remove
void printFirst();
void printSecond();
void printThird();

Foo* fooCreate() {
    Foo* obj = (Foo*) malloc(sizeof(Foo));
    
    // Initialize user defined data here.
    obj->flag = 0;
    return obj;
}

void first(Foo* obj) {
    
    // printFirst() outputs "first". Do not change or remove this line.
    while (obj->flag != 0)
    ;
    printFirst();

    obj->flag++;
}

void second(Foo* obj) {
    
    // printSecond() outputs "second". Do not change or remove this line.
    while (obj->flag < 1)
    ;
    printSecond();
    obj->flag++;
}

void third(Foo* obj) {
    
    // printThird() outputs "third". Do not change or remove this line.
    while (obj->flag < 2)
    ;
    printThird();
}

void fooFree(Foo* obj) {
    // User defined data may be cleaned up here.
    
}