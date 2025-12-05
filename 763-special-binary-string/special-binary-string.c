int cmp(const void* a, const void* b) {
    return strcmp(*(char **)b, *(char **)a);
}

char* makeLargestSpecial(char* s) {
    int n = strlen(s);
    if (n <= 2) return s;

    char** substrs = calloc(n/2 + 1, sizeof(char *));
    int substrs_size = 0;

    int stack = 0;
    int prev = -1;
    for (int curr = 0; curr < n; curr++) {
        if (s[curr] == '1') stack++;
        else stack--;

        if (stack == 0) {
            int inner_len = (curr - prev) - 2; // '1' + SS + '0'
            char *inner = malloc(inner_len + 1);

            strncpy(inner, s + prev + 2, inner_len);
            inner[inner_len] = '\0';

            int chunk_len = curr - prev;
            char *chunk = malloc(chunk_len + 1);

            chunk[0] = '1';
            strcpy(chunk + 1, makeLargestSpecial(inner));
            chunk[chunk_len - 1] = '0';
            chunk[chunk_len] = '\0';

            substrs[substrs_size++] = chunk;

            prev = curr;
        }
    }

    qsort(substrs, substrs_size, sizeof(char*), cmp);

    char* ret = malloc(n+1);
    ret[0] = '\0';
    for (int i = 0; i < substrs_size; i++) 
        strcat(ret, substrs[i]);
    return ret;
}