typedef long long ll;
int waysToSplitArray(int* nums, int numsSize) {
    int n = numsSize;
    ll total = 0;
    for (int i = 0; i < n; i++)
        total += nums[i];

    int cnt = 0;
    ll left_side = 0;
    ll right_side = 0;
    for (int i = 0; i < n - 1; i++) {
        left_side += nums[i];
        right_side = total - left_side;

        if (left_side >= right_side)
            cnt++;
    }
    return cnt;
}