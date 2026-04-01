#define debug(x) cout << #x << " is " << x << endl;

class Solution {
    typedef struct {
        int idx;
        int pos;
        int health;
        int dir;
    } robot_t;
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int n = positions.size();
        vector<robot_t> robots(n);
        for (int i = 0; i < n; i++)
            robots[i] = { i, positions[i], healths[i], directions[i] == 'R'};

        sort(robots.begin(), robots.end(), [](robot_t& A, robot_t& B) {
            return A.pos < B.pos;
        });

        vector<robot_t> st;
        for (robot_t& robot: robots) {
            if (robot.dir)
                st.push_back(robot);
            else {
                while (st.size() && st.back().dir && st.back().health < robot.health) {
                    st.pop_back();
                    robot.health--;
                }

                if (st.size() && st.back().dir && st.back().health > robot.health) 
                    st.back().health--;
                else if (st.size() && st.back().dir && st.back().health == robot.health) 
                    st.pop_back();
                else 
                    st.push_back(robot);
            }
        }

        sort(st.begin(), st.end(), [](robot_t& A, robot_t& B) {
            return A.idx < B.idx;
        });

        vector<int> ret;
        for (robot_t& robot: st)
            ret.push_back(robot.health);
        return ret;
    }
};