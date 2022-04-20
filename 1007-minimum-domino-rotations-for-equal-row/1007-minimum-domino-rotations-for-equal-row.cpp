class Solution {
public:
    vector<int> dp;
    
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
        int N = tops.size();
        
        dp.resize(N+1, -2);        
        vector<int> t = tops, b = bottoms;
        int retTB = flip(0, t[0], t, b); // target at T[0], flip B
        
        dp.clear(); dp.resize(N+1, -2); 
        t = tops, b = bottoms;
        int retBB = flip(0, b[0], t, b); // target at B[0], flip B
        
        dp.clear(); dp.resize(N+1, -2); 
        t = tops, b = bottoms;
        int retBT = flip(0, b[0], b, t);
        
        dp.clear(); dp.resize(N+1, -2); 
        t = tops, b = bottoms;
        int retTT = flip(0, t[0], b, t);
        
        int ret1, ret2;
        if(retTB == -1 && retBB == -1) ret1 = -1;
        else if(retTB == -1) ret1 = retBB;
        else if(retBB == -1) ret1 = retTB;
        else ret1 = min(retTB, retBB);
        
        if(retBT == -1 && retTT == -1) ret2 = -1;
        else if(retBT == -1) ret2 = retTT;
        else if(retTT == -1) ret2 = retBT;
        else ret2 = min(retBT, retTT);
        
        if(ret1 == -1 && ret2 == -1) return -1;
        else if(ret1 == -1) return ret2;
        else if(ret2 == -1) return ret1;
        else return min(ret1, ret2);
    }
    
    int flip(int n, int target, vector<int>& t, vector<int>& b){
        int& ret = dp[n];
        if(ret != -2) return ret;
        if(n == t.size()) return ret = 0;
     
        if(t[n] == target) {
            return ret = flip(n+1, target, t, b);
        }
        else if(b[n] == target){
            swap(t[n], b[n]);
            ret = flip(n+1, target, t, b);
            return (ret == -1)? -1 : 1 + ret;
        }
        else
            return ret =-1;
    }
};
