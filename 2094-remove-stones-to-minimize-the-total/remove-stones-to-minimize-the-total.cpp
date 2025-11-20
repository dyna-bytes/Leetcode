class Solution {
public:
    int minStoneSum(vector<int>& piles, int k) {
        priority_queue<int> pq(piles.begin(), piles.end());
        
        while (k--) {
            int stone = pq.top();
            pq.pop();
            pq.push(stone - stone/2);
        }

        int sum = 0;
        while (pq.size()) {
            sum += pq.top();
            pq.pop();
        }
        return sum;
    }
};