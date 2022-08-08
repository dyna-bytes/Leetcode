class Solution:
    def minCostConnectPoints(self, points: List[List[int]]) -> int:
        def getDist(p1: List[int], p2: List[int]) -> int:
            return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])
        
        N = len(points)
        Tree = Kruskal(N)

        for i in range(N):
            for j in range(i+1, N):
                Tree.insertEdge(i, j, getDist(points[i], points[j]))
        
        return Tree.run()
    
class UnionFind:
    def __init__(self, n: int) -> None:
        self.parent = [-1 for _ in range(n)]
    def find(self, curr: int) -> int:
        if self.parent[curr] < 0: return curr
        self.parent[curr] = self.find(self.parent[curr])
        return self.parent[curr]
    def union(self, a: int, b: int) -> bool:
        a = self.find(a)
        b = self.find(b)
        if a == b: return False
    
        self.parent[b] = a
        return True

class Kruskal:
    def __init__(self, V: int) -> None:
        self.V = V
        self.MST = UnionFind(V)
        self.edges = []
    def insertEdge(self, u: int, v: int, weight: int) -> None:
        self.edges.append([u, v, weight])
    def run(self) -> int:
        self.edges.sort(key = lambda x: x[2])

        res, cnt = 0, 0
        for u, v, weight in self.edges:
            if self.MST.union(u, v):
                res += weight
                cnt += 1
                if cnt == self.V-1: break
        return res