#define max(a, b) (a) > (b) ? (a) : (b)
#define min(a, b) (a) < (b) ? (a) : (b)
typedef long long ll;
int myAtoi(char* s) {
    int n = strlen(s);

    bool sign = true;
    bool found = false;
    ll x = 0;
    for (int i = 0; i < n; i++) {
        if (!found && s[i] == ' ')
            continue;

        if (!found && s[i] == '-') {
            sign = false;
            found = true;
            continue;
        }

        if (!found && s[i] == '+') {
            found = true;
            continue;
        }

        if (s[i] < '0' || s[i] > '9')
            break;
        
        found = true;

        if (x > INT_MAX) break;
        x *= 10;
        x += (s[i] - '0');
    }

    if (sign == false)
        x = -x;

    return min(max(x, INT_MIN), INT_MAX);
}