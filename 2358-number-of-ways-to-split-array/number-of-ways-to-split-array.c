typedef long long ll;
int waysToSplitArray(int* nums, int numsSize) {
    int n = numsSize;
    ll* pref = calloc(n + 1, sizeof(ll));

    for (int i = 0; i < n; i++)
        pref[i + 1] = pref[i] + nums[i];

    int cnt = 0;
    for (int i = 1; i < n; i++)
        if (pref[i] >= pref[n] - pref[i])
            cnt++;
    return cnt;
}