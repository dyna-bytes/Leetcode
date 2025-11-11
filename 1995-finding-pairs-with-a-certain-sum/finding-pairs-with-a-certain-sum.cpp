class FindSumPairs {
    vector<int> nums1, nums2;
    unordered_map<int, int> um;
public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) {
        this->nums1 = nums1;
        this->nums2 = nums2;

        for (int n2: nums2)
            um[n2]++;
    }
    
    void add(int index, int val) {
        um[nums2[index]]--;

        nums2[index] += val;

        um[nums2[index]]++;
    }
    
    int count(int tot) {
        int cnt = 0;
        for (int n1: nums1)
            cnt += um[tot - n1];
        return cnt;
    }
};

/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */