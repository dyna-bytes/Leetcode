class Semaphore {
    int resources;
    pthread_mutex_t m;
    pthread_cond_t cv;
public:
    Semaphore(int resources) : resources(resources) {
        pthread_mutex_init(&m, NULL);
        pthread_cond_init(&cv, NULL);
    }

    void wait() {
        pthread_mutex_lock(&m);
        while (resources <= 0)
            pthread_cond_wait(&cv, &m);

        resources--;
        pthread_mutex_unlock(&m);
    }

    void post() {
        pthread_mutex_lock(&m);
        resources++;
        pthread_cond_signal(&cv);
        pthread_mutex_unlock(&m);
    }
};

class DiningPhilosophers {
    #define MAX_FORKS 5
    Semaphore sem;
    pthread_mutex_t forks[MAX_FORKS];
public:
    DiningPhilosophers() : sem(MAX_FORKS - 1) {
        for (int i = 0; i < MAX_FORKS; ++i)
            pthread_mutex_init(&forks[i], NULL);
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
		int left = philosopher;
        int right = (philosopher + 1) % MAX_FORKS;

        sem.wait();
        pthread_mutex_lock(&forks[left]);
        pthread_mutex_lock(&forks[right]);

        pickLeftFork();
        pickRightFork();

        eat();

        putLeftFork();
        putRightFork();

        pthread_mutex_unlock(&forks[left]);
        pthread_mutex_unlock(&forks[right]);
        sem.post();
    }
};