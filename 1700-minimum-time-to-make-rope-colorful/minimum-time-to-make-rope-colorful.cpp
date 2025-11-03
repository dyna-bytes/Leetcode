class Solution {
public:
    int minCost(string colors, vector<int>& neededTime) {
        int n = colors.size();

        int sum = 0;
        for (int i = 0, j = 0; i < n; ) {
            bool searched = false;
            int runningSum = neededTime[i];
            int maxTime = neededTime[i];
            for (j = i + 1; j < n && colors[j] == colors[i]; j++) {
                maxTime = max(maxTime, neededTime[j]);
                runningSum += neededTime[j];
                searched = true;
            }
            if (searched)
                sum += (runningSum - maxTime);
            i = j;
        }
        return sum;
    }
};