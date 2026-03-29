class PhoneDirectory {
    unordered_set<int> st;
public:
    PhoneDirectory(int maxNumbers) {
        for (int i = 0; i < maxNumbers; i++)
            st.insert(i);
    }
    
    int get() {
        if (st.empty()) return -1;
        int ret = *st.begin();
        st.erase(st.begin());
        return ret;
    }
    
    bool check(int number) {
        return st.find(number) != st.end();
    }
    
    void release(int number) {
        st.insert(number);
    }
};

/**
 * Your PhoneDirectory object will be instantiated and called as such:
 * PhoneDirectory* obj = new PhoneDirectory(maxNumbers);
 * int param_1 = obj->get();
 * bool param_2 = obj->check(number);
 * obj->release(number);
 */