class RLEIterator {
public:
    vector<int> enc;
    int pos = 0;
    int size;
    RLEIterator(vector<int>& encoding) {
        enc = encoding;
        size = encoding.size();
    }
    
    int next(int n) {
        if (pos >= size) return -1;

        while (enc[pos] < n) {
            n -= enc[pos];
            enc[pos] = 0;
            pos += 2;

            if (pos >= size) return -1;
        }

        enc[pos] -= n;
        return enc[pos+1];
    }
};

/**
 * Your RLEIterator object will be instantiated and called as such:
 * RLEIterator* obj = new RLEIterator(encoding);
 * int param_1 = obj->next(n);
 */