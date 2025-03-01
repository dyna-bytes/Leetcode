class Solution {
public:
    int parse_minute(string& time) {
        string s_hour = time.substr(0, 2);
        string s_min = time.substr(3, 2);
        cout << s_hour << ":" << s_min << endl;

        int i_hour = stoi(s_hour);
        int i_min = stoi(s_min);
        return i_hour * 60 + i_min;
    }

    int minute_diff(string& time1, string& time2) {
        int t1 = parse_minute(time1);
        int t2 = parse_minute(time2);
        cout << "t1: " << t1 << " t2: " << t2 << endl;
        
        int diff = ((t2 - t1 + 1440) % 1440);
        if (t2 > t1)
            diff = min(diff, t2 - t1);
        return diff;
    }

    int findMinDifference(vector<string>& timePoints) {
        sort(timePoints.begin(), timePoints.end());
        timePoints.push_back(timePoints[0]);

        int min_diff = INT_MAX;
        for (int i = 0; i < timePoints.size()-1; i++) 
            min_diff = min(min_diff, 
                minute_diff(timePoints[i], timePoints[i+1]));

        return min_diff;
    }
};