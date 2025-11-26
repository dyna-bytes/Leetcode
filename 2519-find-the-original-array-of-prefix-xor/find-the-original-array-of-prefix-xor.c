/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findArray(int* pref, int prefSize, int* returnSize) {
    int* arr = calloc(prefSize, sizeof(int));
    *returnSize = prefSize;

    arr[0] = pref[0];
    for (int i = 1; i < prefSize; i++)
        arr[i] = pref[i - 1] ^ pref[i];
    return arr;
}

/*
 * pref[i] = arr[0] ^ arr[1] ^ ... ^ arr[i]
 * pref[0] = arr[0]
 * pref[1] = arr[0] ^ arr[1] = pref[0] ^ arr[1]
 * => arr[1] = pref[0] ^ pref[1]
*/