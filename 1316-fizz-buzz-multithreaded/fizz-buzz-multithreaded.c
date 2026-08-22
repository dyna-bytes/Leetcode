#define debug(x) printf("[%s](%d) %s is %d\n", __func__, __LINE__, #x, x)
typedef struct {
    int n;
    _Atomic(int) x;
    pthread_mutex_t m;
    pthread_cond_t cv;
} FizzBuzz;

FizzBuzz* fizzBuzzCreate(int n) {
    FizzBuzz* obj = (FizzBuzz*) malloc(sizeof(FizzBuzz));
    obj->n = n;
    obj->x = 1;
    pthread_mutex_init(&obj->m, 0);
    pthread_cond_init(&obj->cv, 0);
    return obj;
}

// Don't change the following declarations
void printNumber(int a);
void printFizz();
void printBuzz();
void printFizzBuzz();

// printFizz() outputs "fizz".
void fizz(FizzBuzz* obj) {
    while (obj->x <= obj->n) {
        pthread_mutex_lock(&obj->m);
        while (((obj->x % 3 != 0) || (obj->x % 5 == 0)) && (obj->x <= obj->n))
            pthread_cond_wait(&obj->cv, &obj->m);

        if (obj->x > obj->n) goto ret;

        printFizz();
        obj->x++;
ret:
        pthread_mutex_unlock(&obj->m);
        pthread_cond_broadcast(&obj->cv);
    }
}

// printBuzz() outputs "buzz".
void buzz(FizzBuzz* obj) {
    while (obj->x <= obj->n) {
        pthread_mutex_lock(&obj->m);
        while (((obj->x % 3 == 0) || (obj->x % 5 != 0)) && (obj->x <= obj->n))
            pthread_cond_wait(&obj->cv, &obj->m);

        if (obj->x > obj->n) goto ret;

        printBuzz();
        obj->x++;
ret:
        pthread_mutex_unlock(&obj->m);
        pthread_cond_broadcast(&obj->cv);
    }
}

// printFizzBuzz() outputs "fizzbuzz".
void fizzbuzz(FizzBuzz* obj) {
    while (obj->x <= obj->n) {
        pthread_mutex_lock(&obj->m);
        while (((obj->x % 3 != 0) || (obj->x % 5 != 0)) && (obj->x <= obj->n))
            pthread_cond_wait(&obj->cv, &obj->m);

        if (obj->x > obj->n) goto ret;

        printFizzBuzz();
        obj->x++;
ret:
        pthread_mutex_unlock(&obj->m);
        pthread_cond_broadcast(&obj->cv);
    }
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.
void number(FizzBuzz* obj) {
    while (obj->x <= obj->n) {
        pthread_mutex_lock(&obj->m);
        while (((obj->x % 3 == 0) || (obj->x % 5 == 0)) && (obj->x <= obj->n))
            pthread_cond_wait(&obj->cv, &obj->m);

        if (obj->x > obj->n) goto ret;

        printNumber(obj->x);
        obj->x++;
ret:
        pthread_mutex_unlock(&obj->m);
        pthread_cond_broadcast(&obj->cv);
    }
}

void fizzBuzzFree(FizzBuzz* obj) {
    
}