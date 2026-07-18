#define debug(x) cout << #x << " is " << x << endl;
class Solution {
    int n = 10;
    const int sample = 123456789;
    const int mask = (int)1e9;
    int getNum(int start, int sz) { // start = 0, sz = 3
        long long num = sample * pow(10, start);
        num %= mask;
        num /= pow(10, n-sz-1);
        return num;
    }
public:
    vector<int> sequentialDigits(int low, int high) {
        int low_sz = to_string(low).size();
        int high_sz = to_string(high).size();

        vector<int> ret;
        for (int sz = low_sz; sz <= high_sz; ++sz) {
            for (int start = 0; start < n - sz; ++start) {
                int num = getNum(start, sz);
                if (num < low || num > high) continue;
                ret.push_back(num);
            }
        }
        return ret;
    }
};