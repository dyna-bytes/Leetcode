class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        primes = {"a": 2, "b": 3, "c": 5, "d": 7, "e": 11, "f": 13, "g": 17,
        "h": 19, "i": 23, "j": 29, "k": 31, "l": 37, "m": 41, "n": 43, "o": 47,
        "p": 53, "q": 59, "r": 61, "s": 67, "t": 71, "u": 73, "v": 79, "w": 83,
        "x": 89, "y": 97, "z": 103}

        products = []
        for str in strs:
            n = 1
            for x in str:
                n *= primes[x]
            products.append(n)

        hash = {}
        ans = []
        for i in range(len(strs)):
            ans_idx = hash.get(products[i])
            if ans_idx == None:
                ans.append([strs[i]])
                hash[products[i]] = len(ans) - 1
            else:
                ans[ans_idx].append(strs[i])
        return ans