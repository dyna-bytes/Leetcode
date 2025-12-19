class Solution {
    typedef pair<int, int> pii;
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        meetings.push_back({0, firstPerson, 0});
        sort(meetings.begin(), meetings.end(), [](vector<int>& l, vector<int>& r){
            return l[2] < r[2];
        });

        int m = meetings.size();
        vector<int> knows(n, false);
        vector<vector<int>> adj(n);

        knows[0] = true;
        knows[firstPerson] = true;

        for (int i = 0, j; i < m; ) {
            int time = meetings[i][2];

            queue<int> q;
            vector<int> people_buffer;

            for (j = i; j < m && meetings[j][2] == time; j++) {
                int x = meetings[j][0];
                int y = meetings[j][1];

                adj[x].push_back(y);
                adj[y].push_back(x);

                people_buffer.push_back(x);
                people_buffer.push_back(y);
            }

            sort(people_buffer.begin(), people_buffer.end());
            people_buffer.erase(unique(people_buffer.begin(), people_buffer.end()),
                 people_buffer.end());

            for (int p: people_buffer)
                if (knows[p])
                    q.push(p);

            while (q.size()) {
                int x = q.front();
                q.pop();

                for (int y: adj[x]) {
                    if (knows[y]) continue;
                    knows[y] = true;
                    q.push(y);
                }
            }

            for (int p: people_buffer)
                adj[p].clear();
                
            i = j;
        }


        vector<int> ret;
        for (int i = 0; i < n; i++)
            if (knows[i]) ret.push_back(i);
        return ret;
    }
};