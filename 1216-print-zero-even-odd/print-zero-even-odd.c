typedef struct {
    int n;
    _Atomic(int) turn;
    pthread_mutex_t m;
    pthread_cond_t cv[3];
} ZeroEvenOdd;

ZeroEvenOdd* zeroEvenOddCreate(int n) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*) malloc(sizeof(ZeroEvenOdd));
    obj->n = n;
    obj->turn = 0;
    pthread_mutex_init(&obj->m, 0);
    for (int i = 0; i < 3; ++i) pthread_cond_init(&obj->cv[i], 0);
    return obj;
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.
void printNumber(int x);
void zero(ZeroEvenOdd* obj) {
    for (int i = 0; i < obj->n; ++i) {
        pthread_mutex_lock(&obj->m);
        while (obj->turn != 0)
            pthread_cond_wait(&obj->cv[0], &obj->m);

        printNumber(0);
        pthread_mutex_unlock(&obj->m);

        if (i % 2 == 0) obj->turn = 1; // call odd
        else obj->turn = 2; // call even
        pthread_cond_broadcast(&obj->cv[obj->turn]);
    }
}

void even(ZeroEvenOdd* obj) {
    for (int i = 2; i <= obj->n; i += 2) {
        pthread_mutex_lock(&obj->m);
        while (obj->turn != 2)
            pthread_cond_wait(&obj->cv[2], &obj->m);

        printNumber(i);
        pthread_mutex_unlock(&obj->m);

        obj->turn = 0;
        pthread_cond_broadcast(&obj->cv[0]);
    }
}

void odd(ZeroEvenOdd* obj) {
    for (int i = 1; i <= obj->n; i += 2) {
        pthread_mutex_lock(&obj->m);
        while (obj->turn != 1)
            pthread_cond_wait(&obj->cv[1], &obj->m);

        printNumber(i);
        pthread_mutex_unlock(&obj->m);

        obj->turn = 0;
        pthread_cond_broadcast(&obj->cv[0]);
    }
}

void zeroEvenOddFree(ZeroEvenOdd* obj) {
    
}