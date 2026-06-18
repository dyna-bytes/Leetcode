typedef struct {
    // User defined data may be declared here.
    pthread_mutex_t m;
    pthread_cond_t cv;
    _Atomic(int) cnt;
} Foo;

// Function Declaration, do not remove
void printFirst();
void printSecond();
void printThird();

Foo* fooCreate() {
    Foo* obj = (Foo*) malloc(sizeof(Foo));
    
    // Initialize user defined data here.
    pthread_mutex_init(&obj->m, 0);
    pthread_cond_init(&obj->cv, 0);
    obj->cnt = 0;
    return obj;
}

void first(Foo* obj) {
    pthread_mutex_lock(&obj->m);
    while (obj->cnt != 0)
        pthread_cond_wait(&obj->cv, &obj->m);
    pthread_mutex_unlock(&obj->m);
    // printFirst() outputs "first". Do not change or remove this line.
    printFirst();

    obj->cnt = 1;
    pthread_cond_broadcast(&obj->cv);
}

void second(Foo* obj) {
    pthread_mutex_lock(&obj->m);
    while (obj->cnt != 1)
        pthread_cond_wait(&obj->cv, &obj->m);
    pthread_mutex_unlock(&obj->m);
    // printSecond() outputs "second". Do not change or remove this line.
    printSecond();

    obj->cnt = 2;
    pthread_cond_broadcast(&obj->cv);
}

void third(Foo* obj) {
    pthread_mutex_lock(&obj->m);
    while (obj->cnt != 2)
        pthread_cond_wait(&obj->cv, &obj->m);
    pthread_mutex_unlock(&obj->m);

    // printThird() outputs "third". Do not change or remove this line.
    printThird();
}

void fooFree(Foo* obj) {
    // User defined data may be cleaned up here.
    
}