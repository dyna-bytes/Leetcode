class MyCalendar {
typedef pair<int, int> pii;
set<pii> books;
bool intersects(int l, int r, int s, int e) {
    return (l < e && s < r);
}

public:
    MyCalendar() { 
    }
    
    bool book(int startTime, int endTime) {
        if (books.size() == 0) {
            books.insert({startTime, endTime});
            return true;
        }

        auto lb = books.lower_bound({startTime, 0});        
        auto ub = books.upper_bound({endTime, 0});   

        if (lb != books.begin()) --lb;     
        
        for (auto it = lb; it != ub; it++) {
            if (intersects(it->first, it->second, startTime, endTime))
                return false;
        }

        books.insert({startTime, endTime});
        return true;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(startTime,endTime);
 */