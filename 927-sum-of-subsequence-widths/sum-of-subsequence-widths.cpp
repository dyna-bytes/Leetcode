class Solution {
    /*
    * from sorted array [A0, A1, ... Ai, ..., Aj ..., A(n-1)]
    * Ai, Aj 를 각각 min, max 로 갖는 subseq 개수 :
    * 2^(j - i - 1)
    * Ai, Aj 를 각각 min, max 로 갖는 subseq 의 width:
    * Aj - Ai
    * Ai, Aj 를 각각 min, max 로 갖는 subseq 의 total width sum:
    * 2^(j - i - 1) * (Aj - Ai)
    * 전체 array 의 total width sum:
    * SUM[i < j]  2^(j - i - 1) * (Aj - Ai)
    */
public:
    typedef long long ll;
    const ll MOD = 1e9 + 7;
    int sumSubseqWidths(vector<int>& A) {
        ll ret = 0;
        int N = A.size();
        vector<ll> pow2(N + 1);
        pow2[0] = 1;
        for (int i = 0; i < N; i++)
            pow2[i + 1] = pow2[i] * 2 % MOD;
        
        sort(A.begin(), A.end());
        for (int i = 0; i < N; i++)
            ret = (ret + (pow2[i] - pow2[N - i - 1]) * A[i] % MOD) % MOD;

        return ret;
    }
};