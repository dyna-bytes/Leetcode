typedef struct {
    int n;
    int x;
    sem_t sem_z;
    sem_t sem_e;
    sem_t sem_o;
} ZeroEvenOdd;
void printNumber(int x);

ZeroEvenOdd* zeroEvenOddCreate(int n) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*) malloc(sizeof(ZeroEvenOdd));
    obj->n = n;
    obj->x = 0;
    sem_init(&obj->sem_z, 0, 1);
    sem_init(&obj->sem_e, 0, 0);
    sem_init(&obj->sem_o, 0, 0);
    return obj;
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.

void zero(ZeroEvenOdd* obj) {
    while (obj->x < obj->n) {
        sem_wait(&obj->sem_z);
        if (obj->x >= obj->n) {
            sem_post(&obj->sem_e);
            sem_post(&obj->sem_o);
            return;
        }
        printNumber(0);
        if (obj->x % 2) sem_post(&obj->sem_e);
        else sem_post(&obj->sem_o);
    }
}

void even(ZeroEvenOdd* obj) {
    while (obj->x < obj->n) {
        sem_wait(&obj->sem_e);
        if (obj->x >= obj->n) {
            sem_post(&obj->sem_z);
            sem_post(&obj->sem_o);
            return;
        }
        printNumber(++obj->x);
        sem_post(&obj->sem_z);
    }
}

void odd(ZeroEvenOdd* obj) {
    while (obj->x < obj->n) {
        sem_wait(&obj->sem_o);
        if (obj->x >= obj->n) {
            sem_post(&obj->sem_z);
            sem_post(&obj->sem_e);
            return;
        }
        printNumber(++obj->x);
        sem_post(&obj->sem_z);
    }
}

void zeroEvenOddFree(ZeroEvenOdd* obj) {
    
}