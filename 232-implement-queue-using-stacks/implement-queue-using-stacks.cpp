class MyQueue {
    stack<int> st;
    stack<int> tmp;
    int front_x;
public:
    MyQueue() {
        front_x = -1;
    }
    
    void push(int x) {
        if (st.empty()) front_x = x;
        st.push(x);
    }
    
    int pop() {
        int x;
        int n = st.size();
        for (int i = 0; i < n - 1; i++) {
            x = st.top();
            st.pop();

            tmp.push(x);
        }

        x = st.top();
        st.pop();

        front_x = tmp.size() ? tmp.top() : -1;
        while (tmp.size()) {
            st.push(tmp.top());
            tmp.pop();
        }
        return x;
    }
    
    int peek() {
        return front_x;
    }
    
    bool empty() {
        return st.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */