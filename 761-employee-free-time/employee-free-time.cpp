/*
// Definition for an Interval.
class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};
*/
#define debug(x) cout << #x << " is " << x << endl;
class Solution {
    typedef pair<int, int> pii;
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        int n = schedule.size();
        map<int, int> events;
        for (auto& sch: schedule) {
            for (Interval& intr: sch) {
                events[intr.start]++;
                events[intr.end]--;
            }
        }

        vector<Interval> ret;
        int open_cnt = 0;
        int start = -1;
        int end = 0;
        for (auto& [time, opens]: events) {
            open_cnt += opens;
            
            if (open_cnt == 0 && start == -1) {
                start = time;
                end = -1;
            } else if (open_cnt && end == -1) {
                end = time;
                ret.push_back(Interval(start, end));
                start = -1;
            }
        }
        return ret;
    }
};