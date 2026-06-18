typedef struct {
    int n;

    pthread_mutex_t m;
    pthread_cond_t cv;
    _Atomic(int) turn;
} FooBar;

// Function declarations. Do not change or remove this line
void printFoo();
void printBar();

FooBar* fooBarCreate(int n) {
    FooBar* obj = (FooBar*) malloc(sizeof(FooBar));
    obj->n = n;

    pthread_mutex_init(&obj->m, 0);
    pthread_cond_init(&obj->cv, 0);
    obj->turn = 0;
    return obj;
}

void foo(FooBar* obj) {
    
    for (int i = 0; i < obj->n; i++) {
        pthread_mutex_lock(&obj->m);
        while (obj->turn != 0)
            pthread_cond_wait(&obj->cv, &obj->m);
        // printFoo() outputs "foo". Do not change or remove this line.
        printFoo();
        obj->turn = 1;
        pthread_cond_signal(&obj->cv);
        pthread_mutex_unlock(&obj->m);
    }
}

void bar(FooBar* obj) {
    
    for (int i = 0; i < obj->n; i++) {
        pthread_mutex_lock(&obj->m);
        while (obj->turn != 1)
            pthread_cond_wait(&obj->cv, &obj->m);
        // printBar() outputs "bar". Do not change or remove this line.
        printBar();
        obj->turn = 0;
        pthread_cond_signal(&obj->cv);
        pthread_mutex_unlock(&obj->m);
    }
}

void fooBarFree(FooBar* obj) {
    pthread_mutex_destroy(&obj->m);   
    pthread_cond_destroy(&obj->cv);
}