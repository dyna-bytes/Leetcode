class Semaphore {
    int count; // "현재 사용 가능한 자원의 수" (음수 안 됨)
    pthread_mutex_t m;
    pthread_cond_t cv;

public:
    Semaphore(int init_token) : count(init_token) {
        pthread_mutex_init(&m, NULL);
        pthread_cond_init(&cv, NULL);
    }

    void wait() {
        pthread_mutex_lock(&m);
        
        while (count == 0) 
            pthread_cond_wait(&cv, &m);
        
        count--; 
        
        pthread_mutex_unlock(&m);
    }

    void signal() {
        pthread_mutex_lock(&m);
        
        count++;
        pthread_cond_signal(&cv);
        
        pthread_mutex_unlock(&m);
    }
};

class DiningPhilosophers {
    Semaphore sem;
    pthread_mutex_t forks[5];
public:
    DiningPhilosophers() : sem(4) {
        for (int i = 0; i < 5; i++)
            pthread_mutex_init(&forks[i], NULL);
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
        int left = philosopher;
        int right = (philosopher + 1) % 5;

		sem.wait();

        pthread_mutex_lock(&forks[left]);
        pthread_mutex_lock(&forks[right]);

        pickLeftFork();
        pickRightFork();
        eat();
        putLeftFork();
        putRightFork();

        pthread_mutex_unlock(&forks[right]);
        pthread_mutex_unlock(&forks[left]);

        sem.signal();
    }
};