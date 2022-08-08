class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        dq = Deque() # 단조 큐. dq([idx, num])로 관리됨. num이 단조감소하는 꼴로 저장됨
        ret = []

        # 어떤 구간에 어떤 값이 포함되어져 있는 것이 아니라
        # 어떤 값이 여러개의 구간에 영향력을 미치는 것이다. (관점의 전환)
        for curr_idx, curr_num in enumerate(nums):
            # 1. 큐의 맨 뒷부분을 보면서, 현재 넣고자 하는 모든 값보다 큐의 원소가 작다면 제거한다.
            while len(dq) > 0 and dq[-1][1] <= curr_num:
                dq.pop()

            # 2. 현재 위치의 값을 넣는다.
            dq.append([curr_idx, curr_num])

            # 3. 큐의 맨 앞부분을 보면서, 현재 위치까지 영향력을 줄 수 없는 모든 원소를 앞에서 제거한다.
            while len(dq) > 0 and dq[0][0] <= curr_idx - k:
                dq.popleft()

            # 4. 큐가 단조감수하는 형태이므로 구간내의 최댓값은 큐의 맨 앞에 있는 값이다.
            ret.append(dq[0][1])
        return ret[max(k-1, 0):]