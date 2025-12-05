int countPartitions(int* nums, int n) {
    int* pref = calloc(n + 1, sizeof(int));

    for (int i = 0; i < n; i++)
        pref[i+1] = pref[i] + nums[i];

    int ans = 0;
    for (int i = 0; i < n - 1; i++) {
        int diff = (pref[n] - pref[i + 1]) - (pref[i + 1]);
        if (diff % 2 == 0) ans++;
    }
    return ans;
}