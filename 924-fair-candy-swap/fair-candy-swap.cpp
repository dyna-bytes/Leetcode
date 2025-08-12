class Solution {
public:
    vector<int> fairCandySwap(vector<int>& aliceSizes, vector<int>& bobSizes) {
        vector<int> ans(2, 0);
        int aliceSum = 0;
        int bobSum = 0;
        int totalSum = 0;

        for (int candy: aliceSizes) aliceSum += candy;
        for (int candy: bobSizes) bobSum += candy;
        totalSum = aliceSum + bobSum;

        for (int aliceCandy: aliceSizes) {
            for (int bobCandy: bobSizes) {
                if (aliceSum - aliceCandy + bobCandy == totalSum/2)  {
                    ans[0] = aliceCandy;
                    ans[1] = bobCandy;
                    break;
                }
            } 
        }

        return ans;
    }
};