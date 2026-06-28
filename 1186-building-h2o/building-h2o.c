#define debug(x) \
    printf("[%s](%d) %s is %d\n", __func__, __LINE__, #x, x)

typedef struct {
    // User defined data may be declared here.
    pthread_mutex_t m;
    pthread_cond_t cv_hy;
    pthread_cond_t cv_ox;
    _Atomic(int) h;
} H2O;

void releaseHydrogen();

void releaseOxygen();

H2O* h2oCreate() {
    H2O* obj = (H2O*) malloc(sizeof(H2O));
    
    // Initialize user defined data here.
    pthread_mutex_init(&obj->m, NULL);
    pthread_cond_init(&obj->cv_hy, NULL);
    pthread_cond_init(&obj->cv_ox, NULL);
    obj->h = 0;
    return obj;
}

void hydrogen(H2O* obj) {
    pthread_mutex_lock(&obj->m);
    while (obj->h == 2)
        pthread_cond_wait(&obj->cv_hy, &obj->m);

    if (++obj->h == 2)
        pthread_cond_signal(&obj->cv_ox);
    // releaseHydrogen() outputs "H". Do not change or remove this line.
    releaseHydrogen();
    pthread_mutex_unlock(&obj->m);
}

void oxygen(H2O* obj) {
    pthread_mutex_lock(&obj->m);
    while (obj->h < 2)
        pthread_cond_wait(&obj->cv_ox, &obj->m);

    obj->h = 0;
    pthread_cond_broadcast(&obj->cv_hy);
    // releaseOxygen() outputs "O". Do not change or remove this line.
    releaseOxygen();
    pthread_mutex_unlock(&obj->m);
}

void h2oFree(H2O* obj) {
    // User defined data may be cleaned up here.
    
}