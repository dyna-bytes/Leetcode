class BoundedBlockingQueue {
    int cap;
    int eq = 0;
    int dq = 0;
    vector<int> q;
    pthread_mutex_t m;
    pthread_cond_t eq_done;
    pthread_cond_t dq_done;
public:
    BoundedBlockingQueue(int capacity) {
        this->cap = capacity + 1;
        q.resize(cap, 0);
        pthread_mutex_init(&m, NULL);
        pthread_cond_init(&eq_done, NULL);
        pthread_cond_init(&dq_done, NULL);
    }
    
    void enqueue(int element) {
        pthread_mutex_lock(&m);
        while (isFull())
            pthread_cond_wait(&dq_done, &m); 

        eq = (eq + 1) % cap;
        q[eq] = element;
        pthread_cond_signal(&eq_done);       

        pthread_mutex_unlock(&m);
    }
    
    int dequeue() {
        pthread_mutex_lock(&m);
        while (isEmpty())
            pthread_cond_wait(&eq_done, &m);
    
        dq = (dq + 1) % cap;
        int element = q[dq];
        pthread_cond_signal(&dq_done);

        pthread_mutex_unlock(&m);
        return element;
    }

    bool isFull() {
        return (eq + 1) % cap == dq;
    }

    bool isEmpty() {
        return eq == dq;
    }
    
    int size() {
        return (eq - dq + cap) % cap;
    }
};