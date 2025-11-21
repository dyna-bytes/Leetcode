class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> set1;
        for (int num: nums1) set1.insert(num);

        vector<int> ret;
        unordered_set<int> set2;

        for (int num: nums2) 
            if (set1.count(num) && !set2.count(num)) {
                set2.insert(num);
                ret.push_back(num);
            }
        return ret;
    }
};