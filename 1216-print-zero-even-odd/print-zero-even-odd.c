
#define debug(x) printf("[%s](%d) %s is %d\n", __func__, __LINE__, #x, x);
typedef struct {
    int n;
    int x;
    int turn_zero;
    pthread_mutex_t m;
    pthread_cond_t cv[3];

    enum {
        ZERO = 0,
        ODD = 1,
        EVEN = 2,
    };
} ZeroEvenOdd;

ZeroEvenOdd* zeroEvenOddCreate(int n) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*) malloc(sizeof(ZeroEvenOdd));
    obj->n = n;
    obj->x = 0;
    obj->turn_zero = true;
    pthread_mutex_init(&obj->m, 0);
    for (int i = 0; i < 3; ++i)
        pthread_cond_init(&obj->cv[i], 0);
    return obj;
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.
void printNumber(int x);
void zero(ZeroEvenOdd* obj) {
    while (true) {
        pthread_mutex_lock(&obj->m);
        while (!obj->turn_zero)
            pthread_cond_wait(&obj->cv[ZERO], &obj->m);

        if (obj->x >= obj->n) {
            ++obj->x;
            pthread_cond_signal(&obj->cv[ODD]);
            pthread_cond_signal(&obj->cv[EVEN]);
            pthread_mutex_unlock(&obj->m);
            return;
        }

        printNumber(0);
        debug(obj->x);
        obj->turn_zero = false;
        ++obj->x;

        if (obj->x % 2)
            pthread_cond_signal(&obj->cv[ODD]);
        else
            pthread_cond_signal(&obj->cv[EVEN]);
        pthread_mutex_unlock(&obj->m);
    }
}

void even(ZeroEvenOdd* obj) {
    while (true) {
        pthread_mutex_lock(&obj->m);
        while ((obj->turn_zero || obj->x % 2) && obj->x <= obj->n)
            pthread_cond_wait(&obj->cv[EVEN], &obj->m);

        if (obj->x > obj->n) {
            obj->turn_zero = true;
            pthread_cond_signal(&obj->cv[ZERO]);
            pthread_cond_signal(&obj->cv[ODD]);
            pthread_mutex_unlock(&obj->m);
            return;
        }

        printNumber(obj->x);
        debug(obj->x);
        obj->turn_zero = true;
        pthread_mutex_unlock(&obj->m);
        pthread_cond_signal(&obj->cv[ZERO]);
    }
}

void odd(ZeroEvenOdd* obj) {
    while (true) {
        pthread_mutex_lock(&obj->m);
        while ((obj->turn_zero || (obj->x % 2 == 0)) && obj->x <= obj->n)
            pthread_cond_wait(&obj->cv[ODD], &obj->m);

        if (obj->x > obj->n) {
            obj->turn_zero = true;
            pthread_cond_signal(&obj->cv[ZERO]);
            pthread_cond_signal(&obj->cv[EVEN]);
            pthread_mutex_unlock(&obj->m);
            return;
        }

        printNumber(obj->x);
        debug(obj->x);
        obj->turn_zero = true;
        pthread_mutex_unlock(&obj->m);
        pthread_cond_signal(&obj->cv[ZERO]);
    }
}

void zeroEvenOddFree(ZeroEvenOdd* obj) {
    
}