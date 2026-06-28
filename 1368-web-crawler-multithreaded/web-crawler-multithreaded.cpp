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
    pthread_mutex_t queueMutex;
    pthread_cond_t queueDone;
    pthread_cond_t taskDone;
    _Atomic(int) shutdown;

    static void* worker(void *args) {
        ThreadPool* obj = (ThreadPool*)args;
        while (true) {
            pthread_mutex_lock(&obj->queueMutex);
            while (obj->taskQueue.empty() && !obj->shutdown)
                pthread_cond_wait(&obj->queueDone, &obj->queueMutex);

            if (obj->taskQueue.empty() && obj->shutdown) {
                pthread_mutex_unlock(&obj->queueMutex);
                break;
            }

            Task* task = obj->taskQueue.front();
            obj->taskQueue.pop();
            pthread_mutex_unlock(&obj->queueMutex);

            task->taskFunc(task->args);

            pthread_mutex_lock(&obj->queueMutex);
            if (obj->taskQueue.empty())
                pthread_cond_signal(&obj->taskDone);
            pthread_mutex_unlock(&obj->queueMutex);
        }

        pthread_cond_broadcast(&obj->taskDone);
        return NULL;
    }
public:
    void submitTask(Task* task) {
        pthread_mutex_lock(&queueMutex);
        taskQueue.push(task);
        pthread_mutex_unlock(&queueMutex);
        pthread_cond_signal(&queueDone);
    }
    void waitAll() {
        pthread_mutex_lock(&queueMutex);
        while (taskQueue.size())
            pthread_cond_wait(&taskDone, &queueMutex);
        pthread_mutex_unlock(&queueMutex);
    }
    ThreadPool(int n) {
        shutdown = false;
        threads.assign(n, NULL);
        pthread_mutex_init(&queueMutex, NULL);
        pthread_cond_init(&queueDone, NULL);
        pthread_cond_init(&taskDone, NULL);
        for (int i = 0; i < n; ++i)
            pthread_create(&threads[i], NULL, &worker, this);
    }
    ~ThreadPool() {
        pthread_mutex_lock(&queueMutex);
        shutdown = true;
        pthread_mutex_unlock(&queueMutex);
        pthread_cond_broadcast(&queueDone);

        for (pthread_t th: threads)   
            pthread_join(th, NULL);
        pthread_mutex_destroy(&queueMutex);
        pthread_cond_destroy(&queueDone);
        pthread_cond_destroy(&taskDone);
    }
};
class Solution {
    HtmlParser* htmlParser;
    ThreadPool* threadPool;
    unordered_set<string> visited;
    mutex visitedMutex;
    static string get_hostname(const string& url) {
        size_t start = url.find("://") + 3;
        size_t end = url.find('/', start);
        return url.substr(start, end - start);
    }
    static void dfs(void *args) {
        UserArgs* uargs = (UserArgs*)args;
        Solution* obj = uargs->obj;
        string currUrl = uargs->arg;
        HtmlParser* htmlParser = obj->htmlParser;
        mutex& visitedMutex = obj->visitedMutex;
        unordered_set<string>& visited = obj->visited;

        string hostname = get_hostname(currUrl);
        // debug(currUrl);

        for (const string& url: htmlParser->getUrls(currUrl)) {
            if (get_hostname(url) != hostname) continue;
            visitedMutex.lock();
            if (visited.count(url)) {
                visitedMutex.unlock();
                continue;
            }

            visited.insert(url);
            visitedMutex.unlock();

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
        this->threadPool = new ThreadPool(512);
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