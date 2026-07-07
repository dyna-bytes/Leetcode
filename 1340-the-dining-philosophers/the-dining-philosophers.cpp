class DiningPhilosophers {
    #define MAXN 5
    sem_t sem;
    pthread_mutex_t m[MAXN];
public:
    DiningPhilosophers() {
        sem_init(&sem, 0, MAXN - 1);
        for (int i = 0; i < MAXN; ++i)
            pthread_mutex_init(&m[i], 0);
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
        sem_wait(&sem);
        int left = philosopher;
        int right = (philosopher + 1) % MAXN;

        pthread_mutex_lock(&m[left]);
        pthread_mutex_lock(&m[right]);

        pickLeftFork();
        pickRightFork();
        eat();
        putLeftFork();
        putRightFork();

        pthread_mutex_unlock(&m[left]);
        pthread_mutex_unlock(&m[right]);

        sem_post(&sem);
    }
};