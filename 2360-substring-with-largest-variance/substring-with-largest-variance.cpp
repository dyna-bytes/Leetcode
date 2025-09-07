#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |"; \
    for (auto e : v) cout << e << "|"; \
    cout << endl; \
} while(0)
class Solution {
public:
    int largestVariance(string s) {
        int maxVar = 0;

        auto kadein = [&](char p, char q) {
            int maxSum = 0;
            int sumP = 0;
            int sumQ = 0;
            bool foundP = false;
            bool foundQ = false;
            for (char ch: s) {
                if (ch == p) sumP++, foundP = true;
                else if (ch == q) sumQ++, foundQ = true;

                if (sumQ > sumP)
                    sumQ = 0, sumP = 0;
                if (sumQ > 0 && maxSum < sumP - sumQ)
                    maxSum = sumP - sumQ;
            }

            sumP = 0, sumQ = 0;
            reverse(s.begin(), s.end());
            for (char ch: s) {
                if (ch == p) sumP++, foundP = true;
                else if (ch == q) sumQ++, foundQ = true;

                if (sumQ > sumP)
                    sumQ = 0, sumP = 0;
                if (sumQ > 0 && maxSum < sumP - sumQ)
                    maxSum = sumP - sumQ;
            }
            return (foundP && foundQ) ? maxSum : 0;
        };

        for (char p = 'a'; p <= 'z'; p++) {
            for (char q = 'a'; q <= 'z'; q++) {
                if (q == p) continue;

                maxVar = max(maxVar,
                            kadein(p, q));
            }
        }
        return maxVar;
    }
};