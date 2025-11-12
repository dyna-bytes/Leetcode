#define debug(x) cout << #x << " is " << x << endl; 

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
    
        int ones = 0;
        for (int i = 0; i < n; i++) 
            if (nums[i] == 1) ones++;

        if (ones) return n - ones;

        int overall_gcd = nums[0];
        for (int i = 1; i < n; i++)
            overall_gcd = __gcd(overall_gcd, nums[i]);
        
        if (overall_gcd > 1) return -1;

        int L = 2;
        while (true) {
            int subgcd = 1;
            for (int i = 0; i <= n - L; i++) {
                subgcd = nums[i];
                for (int j = i + 1; j < i + L; j++)
                    subgcd = __gcd(subgcd, nums[j]);
                
                if (subgcd == 1) break;
            }
            
            if (subgcd == 1) break;
            L++;
        }
        
        return (L - 1) + (n - 1);
    }
};