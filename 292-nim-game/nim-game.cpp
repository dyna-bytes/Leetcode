class Solution {
public:
    bool canWinNim(int n) {
        return n % 4;
        // vector<int> dp(n+1, 0); // dp[x] : win or lose with x stones.
        // dp[1] = true;
        // dp[2] = true;
        // dp[3] = true; // 내가 다 가져가면 상대가 짐
        // dp[4] = false; // 내가 1~3 개 가져가도 상대는 dp[3]~dp[1] => 상대가 이김
        // dp[5] = true; // 내가 1 개 가져가면 상대는 dp[4] => 상대가 짐
        // dp[6] = true; // 내가 2 개 가져가면 상대는 dp[4] => 상대가 짐
        // dp[7] = true; // 내가 3 개 가져가면 상대는 dp[4] => 상대가 짐
        // dp[8] = false; // 내가 1~3 개 가져가면 상대는 dp[7]~dp[5] => 상대가 이김
    }
};