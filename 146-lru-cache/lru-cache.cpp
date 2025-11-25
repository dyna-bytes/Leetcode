#define DEBUG
#ifdef DEBUG
#define debug(x) cout << "[" << __func__ << "]" << #x << " is " << x << endl;
#define debugSeq(s) do { \
    cout << "[" << __func__ << "]" << #s << " is |"; \
    for (auto e : s) cout << "{ " << e.first << ", " << e.second << " }|"; \
    cout << endl; \
} while (0)
#else
#define debug(x)
#define debugSeq(s)
#endif

class LRUCache {
    typedef pair<int, int> pii;
    typedef pii page; // { key, val }
    int size;
    int cap;
    unordered_map<int, list<page>::iterator> lut;
    list<page> pages;
public:
    LRUCache(int capacity) {
        size = 0;
        cap = capacity;
    }
    
    int get(int key) {
        if (lut.count(key) == 0) return -1;

        auto p = lut[key];
        auto [k, v] = *p;
        pages.erase(p);
        pages.push_back({k, v});
        lut[key] = prev(pages.end());
        return v;
    }
    
    void put(int key, int value) {
        if (lut.count(key)) {
            auto p = lut[key];
            auto [k, v] = *p;

            assert(k == key);
            pages.erase(p);
            pages.push_back({key, value});
            lut[key] = prev(pages.end());
            return;
        }

        if (++size > cap) {
            auto p = pages.begin();
            auto [k, v] = *p;

            lut.erase(k);
            pages.pop_front();
            --size;
        } 

        pages.push_back({key, value});
        lut[key] = prev(pages.end());
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */