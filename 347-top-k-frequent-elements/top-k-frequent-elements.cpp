class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> hash;
        for (int num: nums) hash[num]++;

        vector<pair<int, int>> arr;
        for (auto& [num, cnt]: hash)
            arr.push_back({cnt, num});
        sort(arr.begin(), arr.end(), greater<pair<int, int>>());

        vector<int> ret(k);
        for (int i = 0; i < k; i++)
            ret[i] = arr[i].second;
        return ret;
    }
};