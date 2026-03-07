#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |"; \
    for (auto e: v) cout << e << "|"; \
    cout << endl; \
} while (0)

class Solution {
public:
    int minFlips(string s) {
        int n = s.size();
        
        int no_matches_start_odd = 0;   // "101010"
        int no_matches_start_even = 0;  // "010101"
        for (int i = 0; i < n; ++i) {
            bool even = (i % 2 == 0);
            if (s[i] - '0' == even)
                no_matches_start_odd++;
            else 
                no_matches_start_even++;
        }

        if (n % 2 == 0)
            return min(no_matches_start_odd,
                no_matches_start_even);
        

        int ret = n;
        for (int i = 0; i < n; ++i) {
            bool even = (i % 2 == 0);
            swap(no_matches_start_odd,
                no_matches_start_even);
            
            if (s[i] == '1') {
                no_matches_start_odd++;
                no_matches_start_even--;
            } else {
                no_matches_start_odd--;
                no_matches_start_even++;
            }

            ret = min({ ret, 
                no_matches_start_odd,
                no_matches_start_even });
        }
        return ret;
    }
};