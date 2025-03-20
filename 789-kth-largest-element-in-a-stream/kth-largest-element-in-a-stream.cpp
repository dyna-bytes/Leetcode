class KthLargest {
    int K;
    multiset<int, greater<int>> ms;
public:
    KthLargest(int k, vector<int>& nums) {
        K = k;
        ms.insert(nums.begin(), nums.end());
    }
    
    int add(int val) {
        ms.insert(val);
        return *next(ms.begin(), K-1);
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */