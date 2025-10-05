class MedianFinder {
    priority_queue<int, vector<int>, greater<int>> min_heap; // keep size k
    priority_queue<int> max_heap; // keep size k
    int mid;
    int size;
public:
    MedianFinder() {
        mid = -1;
        size = 0;
        max_heap.push(INT_MIN);
        min_heap.push(INT_MAX);
    }
    
    void addNum(int num) {
        if (size % 2 == 0) {
            int topR = min_heap.top();
            int topL = max_heap.top();
            if (topR < num) {
                min_heap.pop();
                min_heap.push(num);
                mid = topR;
            } else if (num < topL) {
                max_heap.pop();
                max_heap.push(num);
                mid = topL;
            } else {
                mid = num;
            }
        } else {
            if (mid < num) {
                max_heap.push(mid);
                min_heap.push(num);
            } else {
                max_heap.push(num);
                min_heap.push(mid);
            }
        }
        size++;
    }
    
    double findMedian() {
        if (size % 2 == 0) {
            return (double)(min_heap.top() + max_heap.top()) / 2;
        } else
            return mid;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */