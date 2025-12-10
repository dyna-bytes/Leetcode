/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void f(int c, int n, int opens, char* path, char** ret, int* retSize) {
    if (c == n) {
        if (opens) return;
        ret[(*retSize)++] = path;
        return;
    }

    {
        char* new_path = calloc(n+1, sizeof(char));
        strcpy(new_path, path);
        strcat(new_path, "(");

        f(c+1, n, opens + 1, new_path, ret, retSize);
    }

    if (opens > 0) {
        char* new_path = calloc(n+1, sizeof(char));
        strcpy(new_path, path);
        strcat(new_path, ")");

        f(c+1, n, opens - 1, new_path, ret, retSize);
    }
}

char** generateParenthesis(int n, int* retSize) {
    *retSize = 0;
    char** ret = calloc(pow(2, 2*n), sizeof(char*));
    
    char* path = "";
    f(0, 2*n, 0, path, ret, retSize);
    return ret;
}