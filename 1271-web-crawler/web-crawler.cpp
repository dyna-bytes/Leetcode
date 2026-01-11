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
        size_t start = url.find("://");
        if (start == string::npos) return "";
        start += 3;
        size_t end = url.find('/', start);
        if (end == string::npos) return url.substr(start);
        return url.substr(start, end - start);
    }
public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        queue<string> q;

        q.push(startUrl);
        visited.insert(startUrl);

        while (q.size()) {
            string currUrl = q.front(); q.pop();

            string hostname = get_hostname(currUrl);
            vector<string> urls = htmlParser.getUrls(currUrl);

            for (string& url: urls) {
                if (hostname != get_hostname(url)) continue;
                if (visited.count(url)) continue;

                visited.insert(url);
                q.push(url);
            }
        }
        
        return vector<string>(visited.begin(), visited.end());
    }
};