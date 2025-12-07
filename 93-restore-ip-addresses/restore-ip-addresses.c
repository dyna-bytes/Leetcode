/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

char* substr(char* str, int s, int n) {
    char* ret = calloc(n + 1, sizeof(char));
    memcpy(ret, str + s, n * sizeof(char));
    ret[n] = '\0';
    return ret;
}
bool isValid(char* str) {
    if (strlen(str) > 3) return false;
    if (str[0] == '0' && strlen(str) > 1) return false;

    int num = atoi(str);
    return 0 <= num && num <= 255;
}

void dfs(int i, int segments, char* path, char* s, char** ret, int* returnSize) {
    if (i == strlen(s)) {
        if (segments == 0) {
            ret[*returnSize] = calloc(strlen(path) + 1, sizeof(char));
            strcpy(ret[*returnSize], path);
            (*returnSize)++;
        }
        return;
    }

    for (int j = i; j < i + 3 && j < strlen(s); j++) {
        char* ss = substr(s, i, j - i + 1);

        if (isValid(ss) && segments > 0) {
            int original_size = strlen(path);
            strcat(path, ss);
            if (segments > 1)
                strcat(path, ".");

            dfs(j + 1, segments - 1, path, s, ret, returnSize);
            path[original_size] = '\0';
        }

        free(ss);
    }
}

char** restoreIpAddresses(char* s, int* returnSize) {
    char** ret = calloc(100, sizeof(char*));
    *returnSize = 0;

    char path[30];
    memset(path, 0, sizeof(path));
    dfs(0, 4, path, s, ret, returnSize);
    return ret;
}