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
        size_t s = url.find("://");
        s += 3;

        size_t e = url.find('/', s);
        if (e == string::npos) return url.substr(s);
        return url.substr(s, e - s);
    }
    void dfs(string& currUrl, HtmlParser& htmlParser) {
        string hostname = get_hostname(currUrl);
        vector<string> urls = htmlParser.getUrls(currUrl);
        for (string& url: urls) {
            if (hostname != get_hostname(url)) continue;
            if (visited.count(url)) continue;
            visited.insert(url);
            dfs(url, htmlParser);
        }
    }
public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        visited.insert(startUrl);
        dfs(startUrl, htmlParser);
        return vector<string>(visited.begin(), visited.end());
    }
};