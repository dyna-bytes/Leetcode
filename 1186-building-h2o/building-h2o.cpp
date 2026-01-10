#define debug(x) cout << "[" << __func__ << "] [" << __LINE__ << "] " << #x << " is " << x << endl;

class H2O {
    int H;
    int O;
    int released;
    pthread_mutex_t m;
    pthread_cond_t cv;
public:
    H2O() {
        H = 0, O = 0;
        released = 0;
        pthread_mutex_init(&m, NULL);
        pthread_cond_init(&cv, NULL);
    }

    void hydrogen(function<void()> releaseHydrogen) {
        pthread_mutex_lock(&m);
        while (H >= 2)
            pthread_cond_wait(&cv, &m);
        H++;

        if (H == 2 && O == 1)
            pthread_cond_broadcast(&cv);
        else
            while (H < 2 || O < 1)
                pthread_cond_wait(&cv, &m);

        releaseHydrogen();
        released++;

        if (released == 3) {
            H = 0;
            O = 0;
            released = 0;
            pthread_cond_broadcast(&cv);
        }
        pthread_mutex_unlock(&m);
    }

    void oxygen(function<void()> releaseOxygen) {
        pthread_mutex_lock(&m);
        while (O >= 1)
            pthread_cond_wait(&cv, &m);
        O++;

        if (H == 2 && O == 1)
            pthread_cond_broadcast(&cv);
        else
            while (H < 2 || O < 1)
                pthread_cond_wait(&cv, &m);

        releaseOxygen();
        released++;

        if (released == 3) {
            H = 0;
            O = 0;
            released = 0;
            pthread_cond_broadcast(&cv);
        }
        pthread_mutex_unlock(&m);
    }
};