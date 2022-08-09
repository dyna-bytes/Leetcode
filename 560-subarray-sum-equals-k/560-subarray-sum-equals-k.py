from typing import List


class Solution:
    def subarraySum(self, nums: List[int], k: int) -> int:
        prf_sum = 0
        ans = 0

        count = {}
        count[prf_sum] = 1
        for num in nums:
            prf_sum += num

            if prf_sum - k in count:
                ans += count[prf_sum - k]
            
            count[prf_sum] = count[prf_sum] + 1 if prf_sum in count else 1

        return ans
