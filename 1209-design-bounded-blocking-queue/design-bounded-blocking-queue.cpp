class BoundedBlockingQueue {
    int eq = 0;
    int dq = 0;
    sem_t sem_eq;
    sem_t sem_dq;
    int cap;
    vector<int> queue;
public:
    BoundedBlockingQueue(int capacity) {
        this->cap = capacity + 1;
        queue.resize(cap);
        sem_init(&sem_eq, 0, 0);
        sem_init(&sem_dq, 0, capacity);
    }
    
    void enqueue(int element) {
        sem_wait(&sem_dq);
        eq = (eq + 1) % cap;
        queue[eq] = element;
        sem_post(&sem_eq);
    }
    
    int dequeue() {
        sem_wait(&sem_eq);
        dq = (dq + 1) % cap;
        int ret = queue[dq];
        sem_post(&sem_dq);
        return ret;
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