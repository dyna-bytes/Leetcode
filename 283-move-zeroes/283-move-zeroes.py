class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        cnt = 0
        i = 0
        while i < len(nums):
            if nums[i] == 0:
                nums.remove(0)
                cnt += 1
            else :
                i += 1 
        
        
        zeros: List[int] = [0 for z in range(cnt)]
        nums += zeros