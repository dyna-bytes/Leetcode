class DiningPhilosophers {
    #define MAX_FORKS 5
    sem_t sem;
    pthread_mutex_t forks[MAX_FORKS];
public:
    DiningPhilosophers() {
        sem_init(&sem, 0, MAX_FORKS - 1);
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

        sem_wait(&sem);
        pthread_mutex_lock(&forks[left]);
        pthread_mutex_lock(&forks[right]);

        pickLeftFork();
        pickRightFork();

        eat();

        putLeftFork();
        putRightFork();

        pthread_mutex_unlock(&forks[left]);
        pthread_mutex_unlock(&forks[right]);
        sem_post(&sem);
    }
};