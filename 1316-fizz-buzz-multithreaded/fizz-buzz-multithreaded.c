// #define DBG
#ifdef DBG
#define debug(x) \
    printf("[%s](%d) %s is %d\n", __func__, __LINE__, #x, x)
#else
#define debug(x)
#endif

typedef struct {
    int n;
    int x;
    pthread_mutex_t m;
    pthread_cond_t c_wake_fizz;
    pthread_cond_t c_wake_buzz;
    pthread_cond_t c_wake_fizzbuzz;
    pthread_cond_t c_wake_number;
    bool wake_fizz;
    bool wake_buzz;
    bool wake_fizzbuzz;
    bool wake_number;
} FizzBuzz;

FizzBuzz* fizzBuzzCreate(int n) {
    FizzBuzz* obj = (FizzBuzz*) malloc(sizeof(FizzBuzz));
    obj->n = n;
    obj->x = 1;
    
    pthread_mutex_init(&obj->m, NULL);
    pthread_cond_init(&obj->c_wake_fizz, NULL);
    pthread_cond_init(&obj->c_wake_buzz, NULL);
    pthread_cond_init(&obj->c_wake_fizzbuzz, NULL);
    pthread_cond_init(&obj->c_wake_number, NULL);
    
    obj->wake_fizz = false;
    obj->wake_buzz = false;
    obj->wake_fizzbuzz = false;
    obj->wake_number = true;

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
        debug(obj->x);

        pthread_mutex_lock(&obj->m);
        while (!obj->wake_fizz)
            pthread_cond_wait(&obj->c_wake_fizz, &obj->m);
        if (obj->x > obj->n) {
            pthread_mutex_unlock(&obj->m);
            return;
        }

        obj->wake_fizz = false;
        printFizz();
        obj->x++;

        if (obj->x > obj->n) {
            obj->wake_fizz = true;
            obj->wake_buzz = true;
            obj->wake_fizzbuzz = true;
            obj->wake_number = true;
            
            pthread_cond_signal(&obj->c_wake_fizz);
            pthread_cond_signal(&obj->c_wake_buzz);
            pthread_cond_signal(&obj->c_wake_fizzbuzz);
            pthread_cond_signal(&obj->c_wake_number);
        } else if (obj->x % 3 == 0 && obj->x % 5 == 0) { 
            obj->wake_fizzbuzz = true;
            pthread_cond_signal(&obj->c_wake_fizzbuzz);
        } else if (obj->x % 3 == 0) {
            obj->wake_fizz = true;
            pthread_cond_signal(&obj->c_wake_fizz);
        } else if (obj->x % 5 == 0) {
            obj->wake_buzz = true;
            pthread_cond_signal(&obj->c_wake_buzz);
        } else {
            obj->wake_number = true;
            pthread_cond_signal(&obj->c_wake_number);
        }

        pthread_mutex_unlock(&obj->m);
    }
}

// printBuzz() outputs "buzz".
void buzz(FizzBuzz* obj) {
    while (true) {
        debug(obj->x);

        pthread_mutex_lock(&obj->m);
        while (!obj->wake_buzz)
            pthread_cond_wait(&obj->c_wake_buzz, &obj->m);
        if (obj->x > obj->n) {
            pthread_mutex_unlock(&obj->m);
            return;
        }

        obj->wake_buzz = false;
        printBuzz();
        obj->x++;

        if (obj->x > obj->n) {
            obj->wake_fizz = true;
            obj->wake_buzz = true;
            obj->wake_fizzbuzz = true;
            obj->wake_number = true;
            
            pthread_cond_signal(&obj->c_wake_fizz);
            pthread_cond_signal(&obj->c_wake_buzz);
            pthread_cond_signal(&obj->c_wake_fizzbuzz);
            pthread_cond_signal(&obj->c_wake_number);
        } else if (obj->x % 3 == 0 && obj->x % 5 == 0) { 
            obj->wake_fizzbuzz = true;
            pthread_cond_signal(&obj->c_wake_fizzbuzz);
        } else if (obj->x % 3 == 0) {
            obj->wake_fizz = true;
            pthread_cond_signal(&obj->c_wake_fizz);
        } else if (obj->x % 5 == 0) {
            obj->wake_buzz = true;
            pthread_cond_signal(&obj->c_wake_buzz);
        } else {
            obj->wake_number = true;
            pthread_cond_signal(&obj->c_wake_number);
        }

        pthread_mutex_unlock(&obj->m);
    }
}

// printFizzBuzz() outputs "fizzbuzz".
void fizzbuzz(FizzBuzz* obj) {
    while (true) {
        debug(obj->x);

        pthread_mutex_lock(&obj->m);
        while (!obj->wake_fizzbuzz)
            pthread_cond_wait(&obj->c_wake_fizzbuzz, &obj->m);
        if (obj->x > obj->n) {
            pthread_mutex_unlock(&obj->m);
            return;
        }

        obj->wake_fizzbuzz = false;
        printFizzBuzz();
        obj->x++;

        if (obj->x > obj->n) {
            obj->wake_fizz = true;
            obj->wake_buzz = true;
            obj->wake_fizzbuzz = true;
            obj->wake_number = true;
            
            pthread_cond_signal(&obj->c_wake_fizz);
            pthread_cond_signal(&obj->c_wake_buzz);
            pthread_cond_signal(&obj->c_wake_fizzbuzz);
            pthread_cond_signal(&obj->c_wake_number);
        } else if (obj->x % 3 == 0 && obj->x % 5 == 0) { 
            obj->wake_fizzbuzz = true;
            pthread_cond_signal(&obj->c_wake_fizzbuzz);
        } else if (obj->x % 3 == 0) {
            obj->wake_fizz = true;
            pthread_cond_signal(&obj->c_wake_fizz);
        } else if (obj->x % 5 == 0) {
            obj->wake_buzz = true;
            pthread_cond_signal(&obj->c_wake_buzz);
        } else {
            obj->wake_number = true;
            pthread_cond_signal(&obj->c_wake_number);
        }

        pthread_mutex_unlock(&obj->m);
    }
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.
void number(FizzBuzz* obj) {    
    while (true) {
        debug(obj->x);

        pthread_mutex_lock(&obj->m);
        while (!obj->wake_number)
            pthread_cond_wait(&obj->c_wake_number, &obj->m);
        if (obj->x > obj->n) {
            pthread_mutex_unlock(&obj->m);
            return;
        }

        obj->wake_number = false;
        printNumber(obj->x);
        obj->x++;

        if (obj->x > obj->n) {
            obj->wake_fizz = true;
            obj->wake_buzz = true;
            obj->wake_fizzbuzz = true;
            obj->wake_number = true;
            
            pthread_cond_signal(&obj->c_wake_fizz);
            pthread_cond_signal(&obj->c_wake_buzz);
            pthread_cond_signal(&obj->c_wake_fizzbuzz);
            pthread_cond_signal(&obj->c_wake_number);
        } else if (obj->x % 3 == 0 && obj->x % 5 == 0) { 
            obj->wake_fizzbuzz = true;
            pthread_cond_signal(&obj->c_wake_fizzbuzz);
        } else if (obj->x % 3 == 0) {
            obj->wake_fizz = true;
            pthread_cond_signal(&obj->c_wake_fizz);
        } else if (obj->x % 5 == 0) {
            obj->wake_buzz = true;
            pthread_cond_signal(&obj->c_wake_buzz);
        } else {
            obj->wake_number = true;
            pthread_cond_signal(&obj->c_wake_number);
        }

        pthread_mutex_unlock(&obj->m);
    }
}

void fizzBuzzFree(FizzBuzz* obj) {
    pthread_mutex_destroy(&obj->m);
    pthread_cond_destroy(&obj->c_wake_fizz);
    pthread_cond_destroy(&obj->c_wake_buzz);
    pthread_cond_destroy(&obj->c_wake_fizzbuzz);
    pthread_cond_destroy(&obj->c_wake_number);

    if (obj)
        free(obj);
}