/*
If current prefix-sum is odd, only care about previous even prefix-sums and vice versa.
arr: [1, 3, 5]
psum: [0, 1, 4, 9]
1 = > 1
4 => 1
9 => 2

arr: [1, 2, 3, 4, 5, 6, 7]
psum: [0, 1, 3, 6, 10, 15, 21, 28]
1 => 1
3 => 1
6 => 2
10 => 2
15 => 3
21 => 3
28 => 4
*/

class Solution {
    const int mod = 1e9 + 7;
public:
    int numOfSubarrays(vector<int>& arr) {
        vector<int> psum(arr.size() + 1, 0);
        int sum = 0;
        int oddPsums = 0;
        int evenPsums = 1;
        for (int i = 0; i < arr.size(); i++) {
            psum[i+1] = (psum[i] + arr[i]) % mod;
            if (psum[i+1] & 1) {
                oddPsums++;
                sum = (sum + evenPsums) % mod;
            } else {
                evenPsums++;
                sum = (sum + oddPsums) % mod;
            }
        }
        return sum;
    }
};

