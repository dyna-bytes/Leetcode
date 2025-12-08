int find(int* nums, int n, int target) {
    int l = 0; 
    int r = n;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (nums[m] < target) l = m;
        else if (nums[m] > target) r = m;
        else return m;
    }

    if (nums[l] == target) return l;
    return -1;
}

int search(int* nums, int numsSize, int target) {
    int n = numsSize;
    int l = 0; // find min
    int r = n - 1;
    if (nums[l] <= nums[r]) {
        int ret = find(nums, n, target);
        return ret;
    }

    while (l < r) {
        int m = (l + r) / 2;
        if (nums[m] < nums[r]) r = m;
        else l = m + 1;

        if (l > 0 && nums[l - 1] > nums[l]) break;
    }

    int ret = find(nums, l, target);
    if (ret != -1) return ret;

    ret = find(nums + l, n - l, target);
    if (ret != -1) return ret + l;

    return -1;
}