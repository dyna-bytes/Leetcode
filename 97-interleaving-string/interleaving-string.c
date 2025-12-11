bool f(int i, int j, int k, char* s1, char* s2, char* s3, int** dp) {
    if (i == strlen(s1))
        return strcmp(s2 + j, s3 + k) == 0;
    if (j == strlen(s2))
        return strcmp(s1 + i, s3 + k) == 0;
    if (dp[i][j] != -1)
        return dp[i][j];

    bool ret = false;
    if (s3[k] == s1[i] && f(i + 1, j, k + 1, s1, s2, s3, dp))
        ret |= true;
    if (s3[k] == s2[j] && f(i, j + 1, k + 1, s1, s2, s3, dp))
        ret |= true;

    return dp[i][j] = ret;
}


bool isInterleave(char* s1, char* s2, char* s3) {
    if (strlen(s1) + strlen(s2) != strlen(s3)) return false;
    
    int** dp = malloc(strlen(s1) * sizeof(int *));
    for (int i = 0; i < strlen(s1); i++) {
        dp[i] = malloc(strlen(s2) * sizeof(int));
        memset(dp[i], -1, strlen(s2) * sizeof(int));
    }

    return f(0, 0, 0, s1, s2, s3, dp);
}