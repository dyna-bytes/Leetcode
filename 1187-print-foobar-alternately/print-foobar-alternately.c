typedef struct {
    int n;
    int foo_turn;
    pthread_mutex_t m;
    pthread_cond_t c;
} FooBar;

// Function declarations. Do not change or remove this line
void printFoo();
void printBar();

FooBar* fooBarCreate(int n) {
    FooBar* obj = (FooBar*) malloc(sizeof(FooBar));
    obj->n = n;
    obj->foo_turn = true;
    pthread_mutex_init(&obj->m, NULL);
    pthread_cond_init(&obj->c, NULL);
    return obj;
}

void foo(FooBar* obj) {
    
    for (int i = 0; i < obj->n; i++) {
        pthread_mutex_lock(&obj->m);
        while (obj->foo_turn == false)
            pthread_cond_wait(&obj->c, &obj->m);

        // printFoo() outputs "foo". Do not change or remove this line.
        printFoo();

        obj->foo_turn = false;
        pthread_cond_signal(&obj->c);
        pthread_mutex_unlock(&obj->m);
    }
}

void bar(FooBar* obj) {
    
    for (int i = 0; i < obj->n; i++) {
        pthread_mutex_lock(&obj->m);
        while (obj->foo_turn == true)
            pthread_cond_wait(&obj->c, &obj->m);
        // printBar() outputs "bar". Do not change or remove this line.
        printBar();
        
        obj->foo_turn = true;
        pthread_cond_signal(&obj->c);
        pthread_mutex_unlock(&obj->m);
    }
}

void fooBarFree(FooBar* obj) {
    pthread_mutex_destroy(&obj->m);   
    pthread_cond_destroy(&obj->c);   
}