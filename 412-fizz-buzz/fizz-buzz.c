/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

char* itoa(int num) {
    char* buf = calloc(20, sizeof(char));
    sprintf(buf, "%d", num);
    return buf;
}

char** fizzBuzz(int n, int* returnSize) {
    char** ans = calloc(n, sizeof(char *));
    *returnSize = n;
    for (int i = 1; i <= n; i++) {
        if (i % 3 == 0 && i % 5 == 0)
            ans[i-1] = "FizzBuzz";
        else if (i % 3 == 0)
            ans[i-1] = "Fizz";
        else if (i % 5 == 0)
            ans[i-1] = "Buzz";
        else
            ans[i-1] = itoa(i);
    }

    return ans;
}