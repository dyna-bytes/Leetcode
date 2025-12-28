#define DBG
#ifdef DBG
#define debug(x) \
    printf("[%s](%d) %s is %d\n", __func__, __LINE__, #x, x)
#else
#define debug(x)
#endif

typedef struct {
    int n;
    int x;
    sem_t sem;
} FizzBuzz;

FizzBuzz* fizzBuzzCreate(int n) {
    FizzBuzz* obj = (FizzBuzz*) malloc(sizeof(FizzBuzz));
    obj->n = n;
    obj->x = 1;
    sem_init(&obj->sem, 0, 0);
    sem_post(&obj->sem);
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
        sem_wait(&obj->sem);
        if (obj->x > obj->n) {
            sem_post(&obj->sem);
            return;
        }

        if ((obj->x % 3 == 0) && (obj->x % 5 != 0)) {
            printFizz();        
            obj->x++;
        }
        sem_post(&obj->sem);
    }
}

// printBuzz() outputs "buzz".
void buzz(FizzBuzz* obj) {
    while (true) {
        sem_wait(&obj->sem);
        if (obj->x > obj->n) {
            sem_post(&obj->sem);
            return;
        }

        if ((obj->x % 3 != 0) && (obj->x % 5 == 0)) {
            printBuzz();
            obj->x++;
        }
        sem_post(&obj->sem);
    }
}

// printFizzBuzz() outputs "fizzbuzz".
void fizzbuzz(FizzBuzz* obj) {
    while (true) {
        sem_wait(&obj->sem);
        if (obj->x > obj->n) {
            sem_post(&obj->sem);
            return;
        }

        if ((obj->x % 3 == 0) && (obj->x % 5 == 0)) {
            printFizzBuzz();
            obj->x++;
        }
        sem_post(&obj->sem);
    }
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.
void number(FizzBuzz* obj) {
    while (true) {
        sem_wait(&obj->sem);
        if (obj->x > obj->n) {
            sem_post(&obj->sem);
            return;
        }

        if ((obj->x % 3 != 0) && (obj->x % 5 != 0)) {
            printNumber(obj->x);
            obj->x++;
        }
        sem_post(&obj->sem);
    }
}

void fizzBuzzFree(FizzBuzz* obj) {
    sem_destroy(&obj->sem);

    if (obj)
        free(obj);
}