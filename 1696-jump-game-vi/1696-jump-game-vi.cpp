class Solution {
public:
    vector<int> dp;
    int maxResult(vector<int>& nums, int k) {
        int n = nums.size();
        dp.resize(n + 1, 0);
        dp[n-1] = nums[n-1];
        
        priority_queue<pair<int, int>> pq;
        pq.push({dp[n-1], n-1});
        
        for(int here = n-2; here >= 0; here--){
            while(!pq.empty() && pq.top().second > min(n-1, here + k))
                pq.pop(); // pq의 최댓값 중 점프할 수 없는 위치의 값들은 제거
            
            dp[here] = pq.top().first + nums[here]; // max(dp[here+1 ~ n-1]) + nums[here]
            pq.push({dp[here], here});
        }
        
        
        return dp[0];
    }
    
};