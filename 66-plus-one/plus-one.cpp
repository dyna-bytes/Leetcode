class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        vector<int> ret(n, 0);

        int c = 1;
        for (int i = n - 1; i >= 0; i--) {
            int x = digits[i] + c;
            c = x / 10;
            ret[i] = x % 10;
        }

        if (c) 
            ret.insert(ret.begin(), c);
        
        return ret;
    }
};