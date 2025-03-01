class Solution {
public:
    const int mod = 1e9 + 7;
    vector<vector<vector<int>>> memo;

    int f(int N, int L, int A) {
        // base case
        if (N == 1) {
            if (L == 2) { // use P or A
                if (A == 1) // use P
                    return 1;
                else // use P or A
                    return 2;
            } else if (L == 1) {
                if (A == 1) // use L or P
                    return 2;
                else // use L or A or P
                    return 3;
            } else if (L == 0) {
                if (A == 1) // use L or P
                    return 2;
                else // use L or P or A
                    return 3;
            }
        }

        int& ret = memo[N][L][A];
        if (ret) return ret;
        
        if (L == 2) { // use P or A
            if (A == 1) { // use P
                ret = (ret + f(N-1, 0, A)) % mod; 
            } else { // use P or A
                ret = (ret + f(N-1, 0, 0)) % mod;
                ret = (ret + f(N-1, 0, 1)) % mod;
            }
        } else if (L == 1) { // use L or A or P
            if (A == 1) { // use L or P
                ret = (ret + f(N-1, 2, A)) % mod;
                ret = (ret + f(N-1, 0, A)) % mod;
            } else { // use L or A or P
                ret = (ret + f(N-1, 2, 0)) % mod;
                ret = (ret + f(N-1, 0, 1)) % mod;
                ret = (ret + f(N-1, 0, 0)) % mod;
            }
        } else if (L == 0) { // use L or A or P
            if (A == 1) { // use L or P
                ret = (ret + f(N-1, 1, A)) % mod;
                ret = (ret + f(N-1, 0, A)) % mod;
            } else { // use L or A or P
                ret = (ret + f(N-1, 1, 0)) % mod;
                ret = (ret + f(N-1, 0, 1)) % mod;
                ret = (ret + f(N-1, 0, 0)) % mod;
            }
        }

        return ret;
    }

    int checkRecord(int n) {
        memo.resize(n+1, vector<vector<int>>(3, vector<int>(2, 0)));

        return f(n, 0, 0);
    }
};