#define max(a, b) ((a) > (b) ? (a) : (b))
int maximumLengthSubstring(char* s) {
    int count[(int)'z' + 1] = {};
    
    int max_len = 0;
    for (int i = 0, j = 0; s[j]; ++j) {
        count[s[j]]++;
        while (count[s[j]] > 2) {
            count[s[i]]--;
            i++;
        }

        max_len = max(max_len, j - i + 1);
    }
    return max_len;
}