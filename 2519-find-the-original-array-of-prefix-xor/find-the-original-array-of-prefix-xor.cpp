class Solution {
public:
    vector<int> findArray(vector<int>& pref) {
        int n = pref.size();
        vector<int> arr(n, 0);

        // pref[0] = arr[0]
        // pref[1] = pref[0] ^ arr[1]
        // pref[2] = pref[0] ^ arr[1] ^ arr[2] = pref[1] ^ arr[2]
        // pref[n+1] = pref[n] ^ arr[n+1]

        // 0 ^ 0 = 0
        // 1 ^ 0 = 1
        // 0 ^ 1 = 1
        // 1 ^ 1 = 0
        // identity: i = 0
        // inverse: a itself

        // pref[n+1] ^ pref[n] = arr[n+1]

        arr[0] = pref[0];
        for (int i = 1; i < n; i++)
            arr[i] = pref[i] ^ pref[i-1];
        return arr;
    }
};