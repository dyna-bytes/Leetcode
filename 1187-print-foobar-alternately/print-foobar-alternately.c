typedef struct {
    int n;
    sem_t foo_done;
    sem_t bar_done;
} FooBar;

// Function declarations. Do not change or remove this line
void printFoo();
void printBar();

FooBar* fooBarCreate(int n) {
    FooBar* obj = (FooBar*) malloc(sizeof(FooBar));
    obj->n = n;
    sem_init(&obj->foo_done, 0, 0);
    sem_init(&obj->bar_done, 0, 0);
    return obj;
}

void foo(FooBar* obj) {
    sem_post(&obj->bar_done);

    for (int i = 0; i < obj->n; i++) {
        sem_wait(&obj->bar_done);
        // printFoo() outputs "foo". Do not change or remove this line.
        printFoo();
        sem_post(&obj->foo_done);
    }
}

void bar(FooBar* obj) {
    
    for (int i = 0; i < obj->n; i++) {
        sem_wait(&obj->foo_done);
        // printBar() outputs "bar". Do not change or remove this line.
        printBar();
        sem_post(&obj->bar_done);
    }
}

void fooBarFree(FooBar* obj) {
    
}