#define ASCII_SIZE 128
#define max(a, b) ((a) < (b) ? (b) : (a))

int lengthOfLongestSubstring(char* str) {
    int n = strlen(str);
    int maxlen = 0;
    int seen[ASCII_SIZE];
    memset(seen, 0, sizeof(seen));

    for (int s = 0, e = 0; s < n && e < n; e++) {
        for (; e < n && seen[str[e]] == 0; e++) 
            seen[str[e]]++;

        seen[str[e]]++;

        maxlen = max(maxlen, e - s);
        for (; s < e && seen[str[e]] > 1; s++)
            seen[str[s]]--;
    }
    return maxlen;
}