#define debug(x) \
    printf("[%s](%d) %s is %d\n", __func__, __LINE__, #x, x)

typedef struct {
    // User defined data may be declared here.
    int h;
    sem_t H;
    sem_t O;
} H2O;

void releaseHydrogen();

void releaseOxygen();

H2O* h2oCreate() {
    H2O* obj = (H2O*) malloc(sizeof(H2O));
    
    // Initialize user defined data here.
    obj->h = 0;
    sem_init(&obj->H, 0, 2);
    sem_init(&obj->O, 0, 0);
    return obj;
}

void hydrogen(H2O* obj) {
    sem_wait(&obj->H);

    ++obj->h;
    if (obj->h == 2){
        sem_post(&obj->O);
        obj->h = 0;
    }
    // releaseHydrogen() outputs "H". Do not change or remove this line.
    releaseHydrogen();
}

void oxygen(H2O* obj) {
    sem_wait(&obj->O);
    // releaseOxygen() outputs "O". Do not change or remove this line.
    releaseOxygen();
    sem_post(&obj->H);
    sem_post(&obj->H);
}

void h2oFree(H2O* obj) {
    // User defined data may be cleaned up here.
    sem_destroy(&obj->H);
    sem_destroy(&obj->O);
    free(obj);
}