#define DBG
#ifdef DBG
#define debug(x) \
    printf("[%s](%d) %s is %d\n", __func__, __LINE__, #x, x)
#else
#define debug(x)
#endif

typedef struct {
    int n;
    int i;
    pthread_mutex_t m;
    pthread_cond_t cv;
} FizzBuzz;

FizzBuzz* fizzBuzzCreate(int n) {
    FizzBuzz* obj = (FizzBuzz*) malloc(sizeof(FizzBuzz));
    obj->n = n;
    obj->i = 1;
    pthread_mutex_init(&obj->m, NULL);
    pthread_cond_init(&obj->cv, NULL);
    return obj;
}

// Don't change the following declarations
void printNumber(int a);
void printFizz();
void printBuzz();
void printFizzBuzz();

// printFizz() outputs "fizz".
void fizz(FizzBuzz* obj) {
    while (true) {
        pthread_mutex_lock(&obj->m);
        while (!((obj->i % 3 == 0) && (obj->i % 5 != 0))
        && (obj->i <= obj->n))
            pthread_cond_wait(&obj->cv, &obj->m);
        pthread_mutex_unlock(&obj->m);
        if (obj->i > obj->n) break;

        printFizz();
        obj->i++;
        pthread_cond_broadcast(&obj->cv);
    }
}

// printBuzz() outputs "buzz".
void buzz(FizzBuzz* obj) {
    while (true) {
        pthread_mutex_lock(&obj->m);
        while (!((obj->i % 3 != 0) && (obj->i % 5 == 0))
        && (obj->i <= obj->n))
            pthread_cond_wait(&obj->cv, &obj->m);
        pthread_mutex_unlock(&obj->m);
        if (obj->i > obj->n) break;

        printBuzz();
        obj->i++;
        pthread_cond_broadcast(&obj->cv);
    }
}

// printFizzBuzz() outputs "fizzbuzz".
void fizzbuzz(FizzBuzz* obj) {
    while (true) {
        pthread_mutex_lock(&obj->m);
        while (!((obj->i % 3 == 0) && (obj->i % 5 == 0))
        && (obj->i <= obj->n))
            pthread_cond_wait(&obj->cv, &obj->m);
        pthread_mutex_unlock(&obj->m);
        if (obj->i > obj->n) break;

        printFizzBuzz();
        obj->i++;
        pthread_cond_broadcast(&obj->cv);
    }
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.
void number(FizzBuzz* obj) {
    while (true) {
        pthread_mutex_lock(&obj->m);
        while (!((obj->i % 3 != 0) && (obj->i % 5 != 0))
        && (obj->i <= obj->n))
            pthread_cond_wait(&obj->cv, &obj->m);
        pthread_mutex_unlock(&obj->m);
        if (obj->i > obj->n) break;

        debug(obj->i);
        printNumber(obj->i);   
        obj->i++;
        pthread_cond_broadcast(&obj->cv);
    }
}

void fizzBuzzFree(FizzBuzz* obj) {
    pthread_mutex_destroy(&obj->m);
    pthread_cond_destroy(&obj->cv);
    free(obj);
}