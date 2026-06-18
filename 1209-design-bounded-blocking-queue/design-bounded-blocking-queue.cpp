class BoundedBlockingQueue {
    sem_t sem_eq;
    sem_t sem_dq;
    int eq;
    int dq;
    int cap;
    vector<int> q;
public:
    BoundedBlockingQueue(int capacity) {
        sem_init(&sem_eq, 0, capacity);
        sem_init(&sem_dq, 0, 0);
        this->cap = capacity + 1;
        q.assign(cap, 0);
        eq = dq = 0;
    }
    
    void enqueue(int element) {
        sem_wait(&sem_eq);
        q[eq = (eq + 1) % cap] = element;
        sem_post(&sem_dq);
    }
    
    int dequeue() {
        sem_wait(&sem_dq);
        int ret = q[dq = (dq + 1) % cap];
        sem_post(&sem_eq);
        return ret;
    }

    bool isFull() {
        return size() == cap - 1;
    }

    bool isEmpty() {
        return eq == dq;
    }
    
    int size() {
        return (eq - dq + cap) % cap;
    }
};