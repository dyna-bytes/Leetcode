class Solution {
public:
    string addBinary(string a, string b) {
        string sum;
        bool carry = false;
        int i, j;
        for (i = a.size() - 1, j = b.size() - 1; i >= 0 || j >= 0; i--, j--) {
            int a_i = i >= 0 ? a[i] - '0' : 0;
            int b_j = j >= 0 ? b[j] - '0' : 0;
            int bitsum = a_i + b_j + carry;
            sum.push_back((bitsum & 1) ? '1' : '0');
            carry = bitsum / 2;
        }

        if (carry)
            sum.push_back('1');
        reverse(sum.begin(), sum.end());
        return sum;
    }
};