#define ASCII_SIZE 128
#define max(a, b) ((a) < (b) ? (b) : (a))
bool check(int s, int e, int** pref) {
    for (int k = 0; k < ASCII_SIZE; k++)
        if (pref[k][e] - pref[k][s] > 1) return false;
    return true;
}

int lengthOfLongestSubstring(char* s) {
    int n = strlen(s);

    int** pref = calloc(ASCII_SIZE, sizeof(int *));
    for (int i = 0; i < ASCII_SIZE; i++)
        pref[i] = calloc(n + 1, sizeof(int));

    for (int i = 0; i < n; i++) {
        char ch = s[i];
        for (int j = 0; j < ASCII_SIZE; j++) 
            pref[j][i + 1] = pref[j][i] + (ch == j);
    }

    int maxlen = 0;
    for (int s = 0, e = 1; s < n && e <= n; ) {
        if (check(s, e, pref)) {
            maxlen = max(maxlen, e - s);
            e++;
        } else
            s++;
    }
    return maxlen;
}