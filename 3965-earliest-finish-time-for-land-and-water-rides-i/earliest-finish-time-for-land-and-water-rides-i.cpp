class Solution {
    vector<int> buf;
    void sort(vector<int>& arr, vector<int>& key,
              bool (*cmp)(vector<int>&, int, int), int s, int e) {
        if (s + 1 >= e)
            return;
        int m = (s + e) / 2;
        sort(arr, key, cmp, s, m);
        sort(arr, key, cmp, m, e);

        int l = s, r = m, k = 0;
        for (; l < m && r < e;)
            if (cmp(key, arr[l], arr[r]))
                buf[k++] = arr[l++];
            else
                buf[k++] = arr[r++];
        while (l < m)
            buf[k++] = arr[l++];
        while (r < e)
            buf[k++] = arr[r++];

        for (int i = 0; i < k; i++)
            arr[i + s] = buf[i];
    }

    static bool comp(vector<int>& key, int l, int r) { return key[l] < key[r]; }

public:
    int earliestFinishTime(vector<int>& landStartTime,
                           vector<int>& landDuration,
                           vector<int>& waterStartTime,
                           vector<int>& waterDuration) {
        int n = landStartTime.size();
        buf.assign(n, 0);

        vector<int> idx_land(n);
        iota(idx_land.begin(), idx_land.end(), 0);
        sort(idx_land, landStartTime, comp, 0, n);

        int m = waterStartTime.size();
        buf.assign(m, 0);
        vector<int> idx_water(m);
        iota(idx_water.begin(), idx_water.end(), 0);
        sort(idx_water, waterStartTime, comp, 0, m);

        int ret = INT_MAX;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                ret = min(ret, max(landStartTime[idx_land[i]] +
                                       landDuration[idx_land[i]],
                                   waterStartTime[idx_water[j]]) +
                                   waterDuration[idx_water[j]]);

        for (int j = 0; j < m; j++)
            for (int i = 0; i < n; i++)
                ret = min(ret, max(waterStartTime[idx_water[j]] +
                                       waterDuration[idx_water[j]],
                                   landStartTime[idx_land[i]]) +
                                   landDuration[idx_land[i]]);
        return ret;
    }
};