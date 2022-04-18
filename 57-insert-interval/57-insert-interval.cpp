class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int n = intervals.size();
        if(n == 0) return {newInterval};
        
        int sn = newInterval[0], se = newInterval[1];
        
        int vecIdxS = 0, vecIdxE = 0;
        bool catchedS = false, catchedE = false;
        for(int i = 0; i < n; i++){
            int S = intervals[i][0], E = intervals[i][1];
            
            if(S <= sn && sn <= E){ catchedS = true; vecIdxS = i; }
            else if(!catchedS && E <= sn){ vecIdxS = i + 1; }
            
            if(S <= se && se <= E){ catchedE = true; vecIdxE = i + 1; }
            else if(!catchedE && E <= se){ vecIdxE = i + 1; }
        }
        
        if(catchedS){
            newInterval[0] = intervals[vecIdxS][0];
        }
        if(catchedE){
            newInterval[1] = intervals[vecIdxE - 1][1];
        }
        
        // 구간[s, e)
        intervals.erase(intervals.begin() + vecIdxS, intervals.begin() + vecIdxE);
        intervals.insert(intervals.begin() + vecIdxS, newInterval);
        return intervals;
    }
};