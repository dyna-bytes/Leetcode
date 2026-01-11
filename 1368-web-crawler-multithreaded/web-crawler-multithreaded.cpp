/**
 * // This is the HtmlParser's API interface.
 * // You should not implement it, or speculate about its implementation
 * class HtmlParser {
 *   public:
 *     vector<string> getUrls(string url);
 * };
 */
#define debug(x) cout << #x << " is " << x << endl;

class ThreadPool {
    size_t num_threads;
    vector<thread> workers;
    queue<function<void()>> jobs;
    atomic<int> active_tasks{0};
    
    condition_variable cv;
    mutex m;
    bool stop_all;
    void work() {
        while (true) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [this]() {
                return !this->jobs.empty() || stop_all;
            });
            
            if (this->jobs.empty() && stop_all) {
                m.unlock();
                return;
            }
            function<void()> job = (jobs.front());
            jobs.pop();
            lock.unlock();
            
            job();
            active_tasks--;
        }
    }
public:
    ThreadPool(size_t num_threads) {
        this->num_threads = num_threads;
        this->stop_all = false;
        for (size_t i = 0; i < num_threads; i++)
            workers.emplace_back([this]() { 
                this->work(); 
            });
    }
    ~ThreadPool() {
        stop_all = true;
        cv.notify_all();
        for (auto& t: workers)
            t.join();
    }
    
    void enqueueJob(function<void()> job) {
        if (stop_all) return;
        
        m.lock();
        active_tasks++;
        jobs.push(job);
        cv.notify_one();
        m.unlock();
    }

    size_t size() {
        return active_tasks;
    }
};

class Solution {
    unordered_set<string> visited;
    mutex m_visited;

    string get_hostname(const string& url) {
        char s[300] = {};
        strcpy(s, url.c_str());
        char* next_p;
        char* p = strtok_r(s, "//", &next_p);
        p = strtok_r(NULL, "/", &next_p);
        return string(p);
    }

    HtmlParser *htmlParser;
    ThreadPool *threadPool;

    void dfs(const string& currUrl) {
        string hostname = get_hostname(currUrl);
        vector<string> urls = htmlParser->getUrls(currUrl);

        for (string& url: urls) {
            if (hostname != get_hostname(url)) continue;
            bool is_new = false;
            {
                lock_guard<mutex> v_lock(m_visited);
                if (visited.count(url) == 0) {
                    visited.insert(url);
                    is_new = true;
                }
            }
            if (is_new)
                threadPool->enqueueJob([this, url](){ dfs(url); });
        }
    }
public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        this->htmlParser = &htmlParser;
        this->threadPool = new ThreadPool(16);

        visited.insert(startUrl);
        threadPool->enqueueJob([&]() { dfs(startUrl); });

        while (threadPool->size()) ;
        delete threadPool;
        
        return vector<string>(visited.begin(), visited.end());
    }
};