#define debug(x) cout << #x << " is " << x << endl;

class Solution {
    int getDivisors(int n) {
        set<int> divisors;
        divisors.insert(1);
        divisors.insert(n);
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                divisors.insert(i);
                divisors.insert(n/i);
            }
        }

        // debug(divisors.size());
        // for (auto d: divisors)
        //     debug(d);
        if (divisors.size() == 4)
            return accumulate(divisors.begin(), divisors.end(), 0);
        return 0;
    }
public:
    int sumFourDivisors(vector<int>& nums) {
        int ret = 0;
        for (int num: nums) {
            ret += getDivisors(num);
        }
        return ret;
    }
};