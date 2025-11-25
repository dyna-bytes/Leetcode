// #define DEBUG
#ifdef DEBUG
#define debug(x) cout << "[" << __func__ << "] " << #x << " is " << x << endl;
#define debugSeq(s) do { \
    cout << "[" << __func__ << "] " << #s << " is |"; \
    for (auto e : s) cout << "{ " << e.first << ", " << e.second << " }|"; \
    cout << endl; \
} while (0)
#else
#define debug(x)
#define debugSeq(s)
#endif

class LFUCache {
    typedef tuple<int, int, int> tiii;
    typedef tiii page; // { key, val, freq }
    int size;
    int cap;
    int minf;
    unordered_map<int, list<page>> freq; // { freq: pages }
    unordered_map<int, list<page>::iterator> lut; // { key, page* } 
public:
    LFUCache(int capacity) {
        size = 0;
        cap = capacity;
        minf = 1;
    }
    
    int get(int key) {
        debug(key);

        if (lut.count(key) == 0) return -1;
        list<page>::iterator p = lut[key];
        auto [k, v, f] = *p;
        
        freq[f].erase(p);
        if (freq[f].empty()) {
            freq.erase(f);
            if (f == minf)
                minf++;
        }

        ++f;
        freq[f].push_back({key, v, f});
        lut[key] = prev(freq[f].end());
        return v;
    }
    
    void put(int key, int value) {
        debug(key);
        debug(value);

        if (lut.count(key)) {
            list<page>::iterator p = lut[key];
            auto [k, v, f] = *p;
            assert(k == key);

            v = value;
            freq[f].erase(p);
            if (freq[f].empty()) {
                freq.erase(f);
                if (f == minf)
                    minf++;
            }

            ++f;
            freq[f].push_back({key, v, f});
            lut[key] = prev(freq[f].end());

            return;
        }

        if (++size > cap) {
            list<page>::iterator p = freq[minf].begin();
            auto [k, v, f] = *p;
            lut.erase(k);

            debug(freq[minf].size());
            freq[minf].pop_front();

            if (freq[minf].empty()) {
                freq.erase(minf);
                if (f == minf)
                    minf++;
            }
            
            --size;
        }

        page p = { key, value, 1 };
        freq[1].push_back(p);
        lut[key] = prev(freq[1].end());
        minf = 1;
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */