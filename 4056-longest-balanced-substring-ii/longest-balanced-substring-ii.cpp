class Solution {
    typedef pair<int, int> pii;
    #define A 0
    #define B 1
    #define C 2
    int n;
    vector<vector<int>> psum; // [s, e) 구간의 char 'a','b','c' 개수
    /* Define distinct
     * 1) a = b = c
     * count_a[i, j] = count_b[i, j] = count_c[i, j]
     * pa[j] - pa[i] = pb[j] - pb[i] = pc[j] - pc[i]
     * pa[j] - pb[j] = pa[i] - pb[i] & pb[j] - pc[j] =  pb[i] - pc[i]
     * Define state[i] = { pa[i] - pb[i], pc[i] - pb[i] }
     *
     * 2) a = b & c = 0
     * count_a[i, j] = count_b[i, j] & count_c[i, j] = 0
     * pa[j] - pb[j] = pa[i] - pb[i] & pc[j] = pc[i]
     * Define state[i] = { pa[i] - pb[i], pc[i] }
     *
     * 3) a = 0 & b = c
     * Define state[i] = { pb[i] - pc[i], pa[i] }
     *
     * 4) b = 0 & c = a
     * Define state[i] = { pc[i] - pa[i], pb[i] }
     *
     * 5) a > 0 & b = c = 0
     * Define state[i] = { pa[i], pb[i], pc[i] } <= 여기서부터는 state 정의보다
     * 단순 반복문 계산이 편리
    */
public:
    int longestBalanced(string s) {
        n = s.size();
        psum.resize(n+1, vector<int>(3, 0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < 3; j++)
                psum[i+1][j] = psum[i][j] + (s[i] - 'a' == j);

        map<pii, int> seen_abc; // { count_a - count_b, count_b - count_c } 
        // count_c - count_a will be automatically same
        map<pii, int> seen_ab_c0; // { count_a - count_b, count_c }
        map<pii, int> seen_bc_a0; // { count_b - count_c, count_a }
        map<pii, int> seen_ca_b0; // { count_c - count_b, count_b }

        // i=0 (빈 문자열)의 초기 상태를 모두 0으로 저장
        seen_abc[{0, 0}] = 0;
        seen_ab_c0[{0, 0}] = 0;
        seen_bc_a0[{0, 0}] = 0;
        seen_ca_b0[{0, 0}] = 0;
        
        int max_len = 0;
        for (int e = 1; e <= n; e++) {
            pii state_abc = { psum[e][A] - psum[e][B], psum[e][B] - psum[e][C] };
            if (seen_abc.count(state_abc))
                max_len = max(max_len, e - seen_abc[state_abc]);
            else
                seen_abc[state_abc] = e;

            pii state_ab_c = { psum[e][A] - psum[e][B], psum[e][C] };
            if (seen_ab_c0.count(state_ab_c))
                max_len = max(max_len, e - seen_ab_c0[state_ab_c]);
            else
                seen_ab_c0[state_ab_c] = e;

            pii state_bc_a = { psum[e][B] - psum[e][C], psum[e][A] };
            if (seen_bc_a0.count(state_bc_a))
                max_len = max(max_len, e - seen_bc_a0[state_bc_a]);
            else
                seen_bc_a0[state_bc_a] = e;

            pii state_ca_b = { psum[e][C] - psum[e][A], psum[e][B] };
            if (seen_ca_b0.count(state_ca_b))
                max_len = max(max_len, e - seen_ca_b0[state_ca_b]);
            else
                seen_ca_b0[state_ca_b] = e;
        }

        for (int i = 0, j = 0; i < n; i++) {
            if (s[i] == 'a') {
                for (j = i; j < n && s[j] == 'a'; j++) ;
                max_len = max(max_len, j - i);
                i = j - 1;
            } else if (s[i] == 'b') {
                for (j = i; j < n && s[j] == 'b'; j++) ;
                max_len = max(max_len, j - i);
                i = j - 1;
            } else { // if (s[i] == 'c')
                for (j = i; j < n && s[j] == 'c'; j++) ;
                max_len = max(max_len, j - i);
                i = j - 1;
            }
        }
        return max_len;
    }
};