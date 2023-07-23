class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        MAX_INT = 2**31 - 1
        n = len(prices)
        profit = 0

        for idx, price in enumerate(prices):
            if idx == 0:
                continue
            if prices[idx - 1] < prices[idx]:
                profit += prices[idx] - prices[idx - 1]
        return profit