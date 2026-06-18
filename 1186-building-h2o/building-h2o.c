#define debug(x) \
    printf("[%s](%d) %s is %d\n", __func__, __LINE__, #x, x)

typedef struct {
    // User defined data may be declared here.
    _Atomic(int) h;
    pthread_mutex_t m;
    pthread_cond_t cv_H;
    pthread_cond_t cv_O;
} H2O;

void releaseHydrogen();

void releaseOxygen();

H2O* h2oCreate() {
    H2O* obj = (H2O*) malloc(sizeof(H2O));
    
    // Initialize user defined data here.
    obj->h = 0;
    pthread_mutex_init(&obj->m, 0);
    pthread_cond_init(&obj->cv_H, 0);
    pthread_cond_init(&obj->cv_O, 0);
    return obj;
}

void hydrogen(H2O* obj) {
    pthread_mutex_lock(&obj->m);
    while (obj->h == 2)
        pthread_cond_wait(&obj->cv_H, &obj->m);
    if (obj->h < 2) ++obj->h;

    // releaseHydrogen() outputs "H". Do not change or remove this line.
    releaseHydrogen();
    pthread_cond_signal(&obj->cv_O);
    pthread_mutex_unlock(&obj->m);
}

void oxygen(H2O* obj) {
    pthread_mutex_lock(&obj->m);
    while (obj->h < 2)
        pthread_cond_wait(&obj->cv_O, &obj->m);
    obj->h = 0;
    // releaseOxygen() outputs "O". Do not change or remove this line.
    releaseOxygen();
    pthread_cond_broadcast(&obj->cv_H);
    pthread_mutex_unlock(&obj->m);
}

void h2oFree(H2O* obj) {
    // User defined data may be cleaned up here.
    pthread_mutex_destroy(&obj->m);
    pthread_cond_destroy(&obj->cv_H);
    pthread_cond_destroy(&obj->cv_O);
    free(obj);
}