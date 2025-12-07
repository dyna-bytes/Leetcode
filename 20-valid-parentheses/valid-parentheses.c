#define STACK_SIZE (1 << 14)
bool isValid(char* s) {
    int n = strlen(s);

    char stk[STACK_SIZE];
    memset(stk, 0, sizeof(stk));
    int sp = 0;

    for (int i = 0; i < n; i++) {
        char ch = s[i];
        if ((ch == '(') || (ch == '[') || (ch == '{'))
            stk[++sp] = ch;
        else if (ch == ')') 
            if (sp && (stk[sp] == '('))
                --sp;
            else return false;
        else if (ch == ']') 
            if (sp && (stk[sp] == '['))
                --sp;
            else return false;
        else if (ch == '}') 
            if (sp && (stk[sp] == '{'))
                --sp;
            else return false;
    }

    return sp == 0;
}