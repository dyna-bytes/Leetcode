class Solution {
    typedef long long ll;
public:
    long long maximumHappinessSum(vector<int>& happiness, int k) {
        sort(happiness.begin(), happiness.end(), greater<int>());
        
        ll sum = 0;
        for (int i = 0; i < k; i++) {
            ll happy = happiness[i];
            happy = max(happy - i, (ll)0);
            sum += happy;
        }
        return sum;
    }
};