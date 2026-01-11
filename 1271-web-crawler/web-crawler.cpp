/**
 * // This is the HtmlParser's API interface.
 * // You should not implement it, or speculate about its implementation
 * class HtmlParser {
 *   public:
 *     vector<string> getUrls(string url);
 * };
 */
#define debug(x) cout << #x << " is " << x << endl;

class Solution {
    unordered_set<string> visited;

    string get_hostname(const string& url) {
        char s[300];
        strcpy(s, url.c_str());
        char* p = strtok(s, "//");
        p = strtok(NULL, "/");
        return string(p);
    }

    HtmlParser *htmlParser;

    void dfs(string& currUrl) {
        string hostname = get_hostname(currUrl);
        vector<string> urls = htmlParser->getUrls(currUrl);

        for (string& url: urls) {
            if (hostname != get_hostname(url)) continue;
            if (visited.count(url)) continue;

            visited.insert(url);
            dfs(url);
        }
    }
public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        this->htmlParser = &htmlParser;
        visited.insert(startUrl);
        dfs(startUrl);
        
        return vector<string>(visited.begin(), visited.end());
    }
};