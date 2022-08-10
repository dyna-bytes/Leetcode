class Solution:
    def shortestSubarray(self, nums: List[int], k: int) -> int:
        dq = Deque() # 누적합이 단조증가 형태로 들어가는 단조큐
        res, prf_sum = float('inf'), 0
    
        dq.append([0, 0])
        for idx, num in enumerate(nums):
            prf_sum += num
            while dq and prf_sum - (smallest_sum := dq[0][1]) >= k:
                res = min(res, idx - dq.popleft()[0] + 1)
            
            while dq and prf_sum <= (largest_sum := dq[-1][1]):
                dq.pop()
            
            dq.append([idx + 1, prf_sum])
        
        return res if res < float('inf') else -1