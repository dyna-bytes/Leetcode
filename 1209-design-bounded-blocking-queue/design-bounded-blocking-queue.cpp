class BoundedBlockingQueue {
    int cap;
    int* q;
    int eq;
    int dq;
    sem_t sem_eq;
    sem_t sem_dq;
public:
    BoundedBlockingQueue(int capacity) {
        this->cap = capacity + 1;
        eq = dq = 0;
        q = (int*)calloc(cap, sizeof(int));
        sem_init(&sem_eq, 0, capacity);
        sem_init(&sem_dq, 0, 0);
    }
    
    void enqueue(int element) {
        sem_wait(&sem_eq);
        q[eq] = element;
        eq = (eq + 1) % cap;
        sem_post(&sem_dq);
    }
    
    int dequeue() {
        sem_wait(&sem_dq);
        int ret = q[dq];
        dq = (dq + 1) % cap;
        sem_post(&sem_eq);
        return ret;
    }
    
    int size() {
        return (eq - dq + cap) % cap;
    }
};