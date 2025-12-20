#define debug(x) \
    printf("[%s](%d) %d\n", __func__, __LINE__, x)

typedef struct {
    // User defined data may be declared here.
    int cnt;
    pthread_mutex_t m;
    pthread_cond_t c;
} Foo;

// Function Declaration, do not remove
void printFirst();
void printSecond();
void printThird();

Foo* fooCreate() {
    Foo* obj = (Foo*) malloc(sizeof(Foo));
    
    // Initialize user defined data here.
    obj->cnt = 0;
    pthread_mutex_init(&obj->m, NULL);
    pthread_cond_init(&obj->c, NULL);

    return obj;
}

void first(Foo* obj) {
    pthread_mutex_lock(&obj->m);
    while (obj->cnt != 0)
        pthread_cond_wait(&obj->c, &obj->m);
    pthread_mutex_unlock(&obj->m);

    // printFirst() outputs "first". Do not change or remove this line.
    printFirst();

    pthread_mutex_lock(&obj->m);
    obj->cnt = 1;
    pthread_cond_broadcast(&obj->c);
    pthread_mutex_unlock(&obj->m);
}

void second(Foo* obj) {
    pthread_mutex_lock(&obj->m);
    while (obj->cnt != 1) 
        pthread_cond_wait(&obj->c, &obj->m);
    pthread_mutex_unlock(&obj->m);
    
    // printSecond() outputs "second". Do not change or remove this line.
    printSecond();

    pthread_mutex_lock(&obj->m);
    obj->cnt = 2;
    pthread_cond_broadcast(&obj->c);
    pthread_mutex_unlock(&obj->m);
}

void third(Foo* obj) {
    pthread_mutex_lock(&obj->m);
    while (obj->cnt != 2)
        pthread_cond_wait(&obj->c, &obj->m);
    pthread_mutex_unlock(&obj->m);
    
    // printThird() outputs "third". Do not change or remove this line.
    printThird();
}

void fooFree(Foo* obj) {
    // User defined data may be cleaned up here.
    pthread_mutex_destroy(&obj->m);   
    pthread_cond_destroy(&obj->c);   

    if (obj)
        free(obj);
}