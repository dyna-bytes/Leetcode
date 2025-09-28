class MinStack {
    typedef pair<int, int> pii;
    stack<pii> st;
    int minVal;
public:
    MinStack() {
        minVal = INT_MAX;
    }
    
    void push(int val) {
        minVal = min(minVal, val);
        st.push({val, minVal});
    }
    
    void pop() {
        st.pop();
        minVal = getMin();
    }
    
    int top() {
        if (st.empty()) return INT_MAX;
        return st.top().first;
    }
    
    int getMin() {
        if (st.empty()) return INT_MAX;
        return st.top().second;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */