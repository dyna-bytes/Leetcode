/**
 * // This is the HtmlParser's API interface.
 * // You should not implement it, or speculate about its implementation
 * class HtmlParser {
 *   public:
 *     vector<string> getUrls(string url);
 * };
 */

#define debug(x) cout << "[" << __func__ << "](" << __LINE__ << #x << " is " << x << endl;
class Solution;
typedef struct {
    Solution* obj;
    string url;
} UserArgs;

typedef struct {
    void (*func)(void*);
    void* userArgs;
} Task;

class ThreadPool {
    queue<Task*> taskQueue;
    vector<pthread_t> threads; 
    pthread_mutex_t mutexQueue;
    pthread_cond_t condQueue;
    pthread_cond_t condDone;
    bool sigkill;
    int activeTasks;
    static void* worker(void *obj) {
        ThreadPool* threadPool = (ThreadPool*)obj;
        while (true) {
            pthread_mutex_lock(&threadPool->mutexQueue);
            while (threadPool->taskQueue.empty() && !threadPool->sigkill)
                pthread_cond_wait(&threadPool->condQueue, &threadPool->mutexQueue);

            if (threadPool->sigkill) {
                pthread_mutex_unlock(&threadPool->mutexQueue);
                return NULL;
            }

            Task* task = threadPool->taskQueue.front();
            threadPool->taskQueue.pop();

            pthread_mutex_unlock(&threadPool->mutexQueue);

            task->func(task->userArgs);

            pthread_mutex_lock(&threadPool->mutexQueue);
            if (--threadPool->activeTasks == 0) 
                pthread_cond_signal(&threadPool->condDone);
            pthread_mutex_unlock(&threadPool->mutexQueue);
        }
    }
public:
    ThreadPool(int n) {
        threads.resize(n);
        pthread_mutex_init(&mutexQueue, 0);
        pthread_cond_init(&condQueue, 0);
        pthread_cond_init(&condDone, 0);
        sigkill = false;
        activeTasks = 0;
        for (int i = 0; i < n; ++i)
            pthread_create(&threads[i], 0, worker, this);
    }
    ~ThreadPool() {
        pthread_mutex_lock(&mutexQueue);
        sigkill = true;
        pthread_mutex_unlock(&mutexQueue);
        pthread_cond_broadcast(&condQueue);

        for (int i = 0; i < threads.size(); ++i)
            pthread_join(threads[i], NULL);
        pthread_mutex_destroy(&mutexQueue);
        pthread_cond_destroy(&condQueue);
        pthread_cond_destroy(&condDone);
    }
    void submitTask(Task* task) {
        pthread_mutex_lock(&mutexQueue);
        taskQueue.push(task);
        activeTasks++;
        pthread_mutex_unlock(&mutexQueue);
        pthread_cond_signal(&condQueue);
    }
    void waitDone() {
        pthread_mutex_lock(&mutexQueue);
        while (activeTasks)
            pthread_cond_wait(&condDone, &mutexQueue);
        pthread_mutex_unlock(&mutexQueue);
    }
};

class Solution {
    unordered_set<string> visited;
    mutex mutexVisited;
    HtmlParser* htmlParser;
    ThreadPool* threadPool;

    static string get_hostname(const string& url) {
        size_t start = url.find("://") + 3;
        size_t end = url.find('/', start);
        return url.substr(start, end - start);
    }

    static void dfs(void *args) {
        UserArgs* uargs = (UserArgs*)args;
        Solution* obj = uargs->obj;
        const string& currUrl = uargs->url;
        const string& hostname = get_hostname(currUrl);

        for (const string& url: obj->htmlParser->getUrls(currUrl)) {
            if (hostname != get_hostname(url)) continue;
            obj->mutexVisited.lock();
            if (obj->visited.count(url)) {
                obj->mutexVisited.unlock();
                continue;
            }
            obj->visited.insert(url);
            obj->mutexVisited.unlock();

            UserArgs* n_uargs = new UserArgs();
            n_uargs->obj = obj;
            n_uargs->url = url;
            Task* task = new Task();
            task->func = &Solution::dfs;
            task->userArgs = n_uargs;

            obj->threadPool->submitTask(task);
        }
    }
public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        this->htmlParser = &htmlParser;
        this->threadPool = new ThreadPool(256);
        visited.insert(startUrl);
        UserArgs* uargs = new UserArgs();
        uargs->obj = this;
        uargs->url = startUrl;
        Task* task = new Task();
        task->func = &Solution::dfs;
        task->userArgs = uargs;
        threadPool->submitTask(task);

        threadPool->waitDone();
        delete threadPool;
        delete uargs;

        return vector<string>(visited.begin(), visited.end());
    }
};