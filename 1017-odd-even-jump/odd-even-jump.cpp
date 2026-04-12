class Solution {
public:
    int oddEvenJumps(vector<int>& arr) {
        int n = arr.size();
        vector<bool> higher(n, 0);
        vector<bool> lower(n, 0);

        higher[n-1] = lower[n-1] = true;

        map<int, int> mp; // {element: index}
        mp[arr[n-1]] = n-1;

        int ret = 1;
        for (int i = n-2; i >= 0; i--) {
            auto greater = mp.lower_bound(arr[i]);
            auto smaller = mp.upper_bound(arr[i]);

            if (greater != mp.end())
                higher[i] = lower[ greater->second ];
            if (smaller != mp.begin())
                lower[i] = higher[ (--smaller)->second ];

            if (higher[i]) ret++;
            mp[arr[i]] = i;
        }
        return ret;
    }
};