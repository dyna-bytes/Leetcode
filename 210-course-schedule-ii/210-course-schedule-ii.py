from queue import Queue
class Solution:
    def findOrder(self, numCourses: int, prerequisites: List[List[int]]) -> List[int]:
        res = []
        indegree = [0 for _ in range(numCourses)]
        adj = [[] for _ in range(numCourses)]

        for first, second in prerequisites:
            adj[first].append(second)
            indegree[second] += 1

        q = Queue()
        for i in range(numCourses):
            if indegree[i] == 0: q.put(i)
        
        count = 0
        while not q.empty():
            curr = q.get()
            res.append(curr)
            count += 1

            for next in adj[curr]:
                
                indegree[next] -= 1
                if indegree[next] == 0: q.put(next)

        if count < numCourses: return []
        return res[::-1]