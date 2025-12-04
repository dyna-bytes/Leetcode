class Solution {
public:
    int countCollisions(string directions) {
        stack<char> st;
        int colli = 0;
        for (char dir: directions) {
            if (dir == 'R') {
                st.push('R');
            } else if (dir == 'S') {
                while (st.size() && st.top() == 'R') {
                    st.pop();
                    colli++;
                }

                st.push('S');
            } else if (dir == 'L') {
                bool hit = false;
                while (st.size() && st.top() == 'R') {
                    st.pop();
                    if (!hit) colli += 2;
                    else colli++;
                    hit = true;
                }

                if (!hit && st.size() && st.top() == 'S') {
                    st.pop();
                    colli++;
                    hit = true;
                }

                if (hit)
                    st.push('S');
            }
        }

        return colli;
    }
};