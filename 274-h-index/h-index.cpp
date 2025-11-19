class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        int H = *max_element(citations.begin(), citations.end());
        int max_h = 0;

        for (int h = 0; h <= H; h++) {
            int cites = 0;
            for (int j = 0; j < n; j++) 
                if (citations[j] >= h) cites++;
            
            if (cites >= h)
                max_h = max(max_h, h);
        }
        return max_h;
    }
};