#define debug(x) cout << "[" << __func__ << "] [" << __LINE__ << "] " << #x << " is " << x << endl;

class H2O {
    int H;
    int O;
    int releaseH;
    int releaseO;
    pthread_mutex_t m;
    pthread_cond_t wakeupH, wakeupO;
public:
    H2O() {
        H = 0, O = 0;
        releaseH = 0, releaseO = 0;
        pthread_mutex_init(&m, NULL);
        pthread_cond_init(&wakeupH, NULL);
        pthread_cond_init(&wakeupO, NULL);
    }

    void hydrogen(function<void()> releaseHydrogen) {
        pthread_mutex_lock(&m);
        while (H >= 2)
            pthread_cond_wait(&wakeupH, &m);        
        H++;

        if (H == 2 && O == 1) {
            pthread_cond_broadcast(&wakeupH);
            pthread_cond_broadcast(&wakeupO);
        } else {
            while (H < 2 || O < 1) 
                pthread_cond_wait(&wakeupH, &m);
        }

        releaseHydrogen();
        releaseH++;

        if (releaseH == 2 && releaseO == 1) {
            H = 0, O = 0;
            releaseH = 0, releaseO = 0;
            pthread_cond_broadcast(&wakeupH);
            pthread_cond_broadcast(&wakeupO);
        }
        
        pthread_mutex_unlock(&m);
    }

    void oxygen(function<void()> releaseOxygen) {
        pthread_mutex_lock(&m);
        while (O >= 1)
            pthread_cond_wait(&wakeupO, &m);
        O++;
    
        if (H == 2 && O == 1) {     
            pthread_cond_broadcast(&wakeupH);
            // pthread_cond_signal(&wakeupH);
        } else {
            while (H < 2 || O < 1) 
                pthread_cond_wait(&wakeupO, &m);
        }
        
        releaseOxygen();
        releaseO++;
        
        if (releaseH == 2 && releaseO == 1) {
            H = 0, O = 0;
            releaseH = 0, releaseO = 0;
            pthread_cond_broadcast(&wakeupH);
            pthread_cond_broadcast(&wakeupO);
        }

        pthread_mutex_unlock(&m);
    }
};
