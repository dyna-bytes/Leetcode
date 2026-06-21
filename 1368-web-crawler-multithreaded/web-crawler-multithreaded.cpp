/**
 * // This is the HtmlParser's API interface.
 * // You should not implement it, or speculate about its implementation
 * class HtmlParser {
 *   public:
 *     vector<string> getUrls(string url);
 * };
 */

#define debug(x) cout << #x << " is " << x << endl;
class Solution;
struct UserArgs {
    Solution* obj;
    string arg;
};
struct Task {
    void (*taskFunc)(void*);
    void* args;
};
class ThreadPool {
    vector<pthread_t> threads;
    queue<Task*> taskQueue;
    pthread_mutex_t mutexQueue;
    pthread_cond_t condQueue;
    pthread_cond_t condDone;
    bool shutdown = false;
    int n_threads;

    static void* worker(void *args) {
        ThreadPool* obj = (ThreadPool*)(args);
        while (true) {
            pthread_mutex_lock(&obj->mutexQueue);
            while (obj->taskQueue.empty() && !obj->shutdown) 
                pthread_cond_wait(&obj->condQueue, &obj->mutexQueue);
            
            if (obj->shutdown && obj->taskQueue.empty()) {
                pthread_mutex_unlock(&obj->mutexQueue);
                break;
            }

            Task* task = obj->taskQueue.front();
            obj->taskQueue.pop();
            pthread_mutex_unlock(&obj->mutexQueue);

            task->taskFunc(task->args);
            // delete (UserArgs*)(task->args); 
            // delete task;

            pthread_mutex_lock(&obj->mutexQueue);
            if (obj->taskQueue.empty()) 
                pthread_cond_signal(&obj->condDone);
            pthread_mutex_unlock(&obj->mutexQueue);
        }
        return NULL;
    }
public:
    void submitTask(Task* task) {
        pthread_mutex_lock(&mutexQueue);
        taskQueue.push(task);
        pthread_mutex_unlock(&mutexQueue);
        pthread_cond_signal(&condQueue);
    }
    void waitAll() {
        pthread_mutex_lock(&mutexQueue);
        while (!taskQueue.empty())
            pthread_cond_wait(&condDone, &mutexQueue);
        pthread_mutex_unlock(&mutexQueue);
    }
    ThreadPool(int n_threads) {
        this->n_threads = n_threads;
        pthread_mutex_init(&mutexQueue, NULL);
        pthread_cond_init(&condQueue, NULL);
        pthread_cond_init(&condDone, NULL);

        threads.assign(n_threads, 0);
        for (int i = 0; i < n_threads; ++i)
            pthread_create(&threads[i], 0, &worker, this);
    }
    ~ThreadPool() {
        pthread_mutex_lock(&mutexQueue);
        shutdown = true;
        pthread_mutex_unlock(&mutexQueue);

        pthread_cond_broadcast(&condQueue);
        for (int i = 0; i < n_threads; ++i)
            pthread_join(threads[i], NULL);
        pthread_mutex_destroy(&mutexQueue);
        pthread_cond_destroy(&condQueue);
        pthread_cond_destroy(&condDone);
    }
};

class Solution {
    unordered_set<string> visited;
    mutex mutexVisited;

    HtmlParser *htmlParser;
    ThreadPool *threadPool;

    static string get_hostname(const string& url) {
        size_t start = url.find("://") + 3;
        size_t end = url.find('/', start);
        return url.substr(start, end - start);
    }
    static void dfs(void *args) {
        UserArgs* uargs = (UserArgs*)(args);
        Solution* obj = uargs->obj;
        string currUrl = uargs->arg;
        string hostname = get_hostname(currUrl);
        debug(currUrl);

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
            n_uargs->arg = url;
            Task* task = new Task();
            task->taskFunc = &Solution::dfs;
            task->args = n_uargs;
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
        uargs->arg = startUrl;
        Task* task = new Task();
        task->taskFunc = &Solution::dfs;
        task->args = uargs;
        threadPool->submitTask(task);

        threadPool->waitAll();
        delete threadPool;
        delete uargs;

        return vector<string>(visited.begin(), visited.end());
    }
};