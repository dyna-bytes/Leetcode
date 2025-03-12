class Solution {
typedef long long ll;
typedef vector<ll> vll;
vll evens;
public:
    vector<long long> maximumEvenSplit(long long finalSum) {
        if (finalSum & 1) return evens;     

        ll even = 2;
        ll currentSum = 0;
        while (currentSum + even <= finalSum) {
            currentSum += even;
            evens.push_back(even);
            even += 2;
        }

        ll leftOver = finalSum - currentSum;
        evens.back() += leftOver;

        return evens;
    }
};