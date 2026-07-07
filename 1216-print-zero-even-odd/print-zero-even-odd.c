typedef struct {
    int n;
    int curr;
    int state; // 0: ZERO 차례, 1: ODD 차례, 2: EVEN 차례
    pthread_mutex_t m;
    pthread_cond_t cv[3];
} ZeroEvenOdd;

ZeroEvenOdd* zeroEvenOddCreate(int n) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*) malloc(sizeof(ZeroEvenOdd));
    obj->n = n;
    obj->curr = 1;
    obj->state = 0; // 시작은 무조건 ZERO
    
    pthread_mutex_init(&obj->m, NULL);
    for (int i = 0; i < 3; ++i) {
        pthread_cond_init(&obj->cv[i], NULL);
    }
    return obj;
}
void printNumber(int x);
void zero(ZeroEvenOdd* obj) {
    // zero는 무조건 n번 출력함
    for (int i = 0; i < obj->n; ++i) {
        pthread_mutex_lock(&obj->m);
        
        while (obj->state != 0) {
            pthread_cond_wait(&obj->cv[0], &obj->m);
        }
        
        printNumber(0);
        
        // 다음에 출력할 숫자가 홀수인지 짝수인지 판별하여 상태 변경
        if (obj->curr % 2 == 1) {
            obj->state = 1; 
            pthread_cond_signal(&obj->cv[1]); // ODD 전용 CV만 깨움
        } else {
            obj->state = 2; 
            pthread_cond_signal(&obj->cv[2]); // EVEN 전용 CV만 깨움
        }
        
        pthread_mutex_unlock(&obj->m);
    }
}

void even(ZeroEvenOdd* obj) {
    // 짝수는 2부터 시작해서 2씩 증가하며 n까지 출력함
    for (int i = 2; i <= obj->n; i += 2) {
        pthread_mutex_lock(&obj->m);
        
        while (obj->state != 2) {
            pthread_cond_wait(&obj->cv[2], &obj->m);
        }
        
        printNumber(obj->curr);
        obj->curr++;
        
        obj->state = 0; // 다시 ZERO 차례로 넘김
        pthread_cond_signal(&obj->cv[0]); // ZERO 전용 CV만 깨움
        
        pthread_mutex_unlock(&obj->m);
    }
}

void odd(ZeroEvenOdd* obj) {
    // 홀수는 1부터 시작해서 2씩 증가하며 n까지 출력함
    for (int i = 1; i <= obj->n; i += 2) {
        pthread_mutex_lock(&obj->m);
        
        while (obj->state != 1) {
            pthread_cond_wait(&obj->cv[1], &obj->m);
        }
        
        printNumber(obj->curr);
        obj->curr++;
        
        obj->state = 0; // 다시 ZERO 차례로 넘김
        pthread_cond_signal(&obj->cv[0]); // ZERO 전용 CV만 깨움
        
        pthread_mutex_unlock(&obj->m);
    }
}

void zeroEvenOddFree(ZeroEvenOdd* obj) {
    pthread_mutex_destroy(&obj->m);
    for (int i = 0; i < 3; ++i) {
        pthread_cond_destroy(&obj->cv[i]);
    }
    free(obj);
}