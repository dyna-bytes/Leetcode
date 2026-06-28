#define debug(x) \
    printf("[%s](%d) %s is %d\n", __func__, __LINE__, #x, x)
    
typedef struct {
    // User defined data may be declared here.
    sem_t sem_hy;
    sem_t sem_ox;
    _Atomic(int) h;
} H2O;

void releaseHydrogen();

void releaseOxygen();

H2O* h2oCreate() {
    H2O* obj = (H2O*) malloc(sizeof(H2O));
    
    // Initialize user defined data here.
    sem_init(&obj->sem_hy, 0, 2);
    sem_init(&obj->sem_ox, 0, 0);
    obj->h = 0;
    return obj;
}

void hydrogen(H2O* obj) {
    sem_wait(&obj->sem_hy);

    if (++obj->h == 2)
        sem_post(&obj->sem_ox);
    // releaseHydrogen() outputs "H". Do not change or remove this line.
    releaseHydrogen();
}

void oxygen(H2O* obj) {
    sem_wait(&obj->sem_ox);
    obj->h = 0;

    // releaseOxygen() outputs "O". Do not change or remove this line.
    releaseOxygen();

    sem_post(&obj->sem_hy);
    sem_post(&obj->sem_hy);
}

void h2oFree(H2O* obj) {
    // User defined data may be cleaned up here.
    
}