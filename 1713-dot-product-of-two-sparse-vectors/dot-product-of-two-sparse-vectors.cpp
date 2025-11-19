#define debug(x) cout << #x << " is " << x << endl;
class SparseVector {
    map<int, int> um;
public:
    SparseVector(vector<int> &nums) {
        for (int i = 0; i < nums.size(); i++)
            if (nums[i]) um[i] = nums[i];
    }
    
    // Return the dotProduct of two sparse vectors
    int dotProduct(SparseVector& vec) {
        auto it = um.begin();
        auto jt = vec.um.begin();

        int ans = 0;
        for (; it != um.end() && jt != vec.um.end(); ) {
            if (it->first == jt->first) {
                ans += (it->second * jt->second);
                ++it;
                ++jt;
            }
            else if (it->first < jt->first)
                ++it;
            else
                ++jt;
        }
        return ans;
    }
};

// Your SparseVector object will be instantiated and called as such:
// SparseVector v1(nums1);
// SparseVector v2(nums2);
// int ans = v1.dotProduct(v2);