class StockPrice {
    typedef pair<int, int> pii; // {price, time}
    pii latest;
    unordered_map<int, int> prices; // {time, price}
    multiset<pii> records;

public:
    StockPrice() { latest = {-1, -1}; }

    void update(int timestamp, int price) {
        auto& [p, t] = latest;
        if (t <= timestamp) {
            t = timestamp;
            p = price;
        }

        if (!records.empty())
            records.erase({prices[timestamp], timestamp});
        records.insert({price, timestamp});

        prices[timestamp] = price;
    }

    int current() { return latest.first; }

    int maximum() { return records.rbegin()->first; }

    int minimum() { return records.begin()->first; }
};

/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice* obj = new StockPrice();
 * obj->update(timestamp,price);
 * int param_2 = obj->current();
 * int param_3 = obj->maximum();
 * int param_4 = obj->minimum();
 */