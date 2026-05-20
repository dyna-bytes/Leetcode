class Solution {
    typedef unsigned long long ull;
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        int n = A.size();
        vector<int> C(n);
        ull a = 0, b = 0;
        for (int i = 0; i < n; i++) {
            a |= (1LL << A[i]);
            b |= (1LL << B[i]);

            ull c = a & b;
            C[i] = popcount(c);
        }
        return C;
    }
};