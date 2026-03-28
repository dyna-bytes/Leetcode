class Solution {
public:
    int shortestWay(string source, string target) {
        for (char t: target) 
            if (source.find(t) == string::npos) return -1;
        
        list<char> tar(target.begin(), target.end());
        int ret = 0;

        while (tar.size()) {
            list<char> src(source.begin(), source.end());
            while (src.size()) {
                if (src.front() == tar.front()) {
                    src.erase(src.begin());
                    tar.erase(tar.begin());
                } else
                    src.erase(src.begin());
            }
            ret++;
        }

        return ret;
    }
};