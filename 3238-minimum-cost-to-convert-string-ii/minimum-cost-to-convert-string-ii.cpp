#define debug(x) cout << #x << " is " << x << endl;

struct Trie {
    Trie *child[26];
    int id; // 이 노드에서 끝나는 문자열의 ID (없으면 -1)

    Trie() {
        for (int i = 0; i < 26; i++) child[i] = nullptr;
        id = -1;
    }
    void insert(const char *str, int id) {
        if (*str == '\0') {
            this->id = id;
            return;
        } 

        if (child[*str - 'a'] == nullptr)
            child[*str - 'a'] = new Trie;
        child[*str - 'a']->insert(str + 1, id);
    }
    ~Trie() {
        for (int i = 0; i < 26; i++)
            if (child[i]) delete child[i];
    }
};

class Solution {
    typedef long long ll;
    typedef pair<ll, ll> pll;
    const ll INF = 1e14;

    map<string, ll> hash;
    vector<vector<ll>> mp;
    vector<vector<pll>> adj;
    Trie* root;
    vector<ll> dp; // dp[i] : source[:i] 를 target[:i] 로 변환하는데 드는 최소 비용
    /* len := 인덱스 i에서 끝나는 세그먼트 길이
     * dp[i] = min(
     * 세그먼트 변환 비용 (source[i-len:i] -> target[i:len:i]) + dp[i-len] ( = cost[ source[i-len:i] ][ target[i-len:i] ] + dp[i-len])
     * dp[i-1] (만약 source[i-1] = target[i-1] 인 경우) 
     * INF (둘 다 아닌 경우)
     * )
    */

    ll solve_dp(string& source, string& target) {
        int len_src = source.size();
        dp[0] = 0;
        for (int i = 0; i < len_src; i++) {
            if (dp[i] >= INF) continue;

            // Case A: 문자가 동일하면 비용 0으로 한 칸 전진
            if (source[i] == target[i]) 
                dp[i + 1] = min(dp[i + 1], dp[i]);
            
            // Case B: Trie를 타고 가면서 변환 가능한 구간 탐색
            Trie* p_src = root;
            Trie* p_trg = root;

            // i부터 시작해서 가능한 길이만큼 Trie를 동시에 내려감
            for (int len = 0; i + len < len_src; len++) {
                int char_src = source[i + len] - 'a';
                int char_trg = target[i + len] - 'a';

                // Trie 경로가 없으면 더 이상 긴 문자열도 매칭 불가 -> break
                if (!p_src->child[char_src] || !p_trg->child[char_trg]) break;

                p_src = p_src->child[char_src];
                p_trg = p_trg->child[char_trg];

                // 두 경로 모두 유효한 단어 ID를 가지고 있다면 -> 변환 시도
                if (p_src->id != -1 && p_trg->id != -1) {
                    int u = p_src->id;
                    int v = p_trg->id;
                    if (mp[u][v] >= INF) continue;
                    dp[i + len + 1] = min(dp[i + len + 1], dp[i] + mp[u][v]);
                }
            }
        }

        return dp[source.size()];
    }

    void bfs(int start) {
        priority_queue<pll, vector<pll>, greater<pll>> pq;
        mp[start][start] = 0;
        pq.push({ 0, start });

        while (pq.size()) {
            auto [dist, curr] = pq.top(); pq.pop();

            if (mp[start][curr] < dist) continue;

            for (auto& [next, cost]: adj[curr]) {
                if (mp[start][next] <= cost + dist) continue;
                mp[start][next] = cost + dist;
                pq.push({ cost + dist, next });
            }
        }
    }
    
public:
    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
        if (source.size() != target.size()) return -1;

        root = new Trie();
        for (string& s: original)
            if (hash.count(s) == 0) {
                hash[s] = hash.size() + 1;
                root->insert(s.c_str(), hash[s]);
            }
        for (string& s: changed)
            if (hash.count(s) == 0) {
                hash[s] = hash.size() + 1;
                root->insert(s.c_str(), hash[s]);
            }

        mp.resize(hash.size() + 1, vector<ll>(hash.size() + 1, INF));
        adj.resize(hash.size() + 1);

        for (int i = 0; i < original.size(); i++) {
            int u = hash[original[i]];
            int v = hash[changed[i]];
            adj[u].push_back({ v, (ll)cost[i] });
        }

        for (int i = 1; i <= hash.size(); i++)
            bfs(i);

        dp.resize(source.size() + 1, INF);

        ll ret = solve_dp(source, target);
        if (ret >= INF) return -1;
        return ret;
    }
};