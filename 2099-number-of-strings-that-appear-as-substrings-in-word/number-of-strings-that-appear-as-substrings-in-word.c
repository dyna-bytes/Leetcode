int numOfStrings(char** patterns, int patternsSize, char* word) {
    int ret = 0;
    for (int i = 0; i < patternsSize; ++i) {
        char* pattern = patterns[i];
        for (int j = 0; word[j] != '\0'; ++j) {
            if (word[j] != pattern[0]) continue;
            
            int k;
            for (k = 0; word[j + k] != '\0' && pattern[k] != '\0'; ++k)
                if (word[j + k] != pattern[k]) break;

            if (pattern[k] == '\0') {
                ret++;
                break;
            }
        }
    }
    return ret;
}