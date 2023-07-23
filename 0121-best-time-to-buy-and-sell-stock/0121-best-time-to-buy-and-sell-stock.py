class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)
        l = r = 0
        profit = maxProfit = 0
        
        while r < n:
            profit = prices[r] - prices[l]
            maxProfit = max(maxProfit, profit)
            
            if profit < 0:
                l += 1
                r = l
            else:
                r += 1
        return maxProfit