/**
 * // This is the HtmlParser's API interface.
 * // You should not implement it, or speculate about its implementation
 * class HtmlParser {
 *   public:
 *     vector<string> getUrls(string url);
 * };
 */
class Solution;
struct UserArgs {
    Solution *obj;
    string arg;
};

struct Task {
    void (*taskFunction)(void *);
    void *args;
};

class ThreadPool {
    vector<pthread_t> threads;
    queue<Task*> taskQueue;
    pthread_mutex_t mutexQueue;
    pthread_cond_t condQueue;
    pthread_cond_t condDone;

    bool shutdown;

    void worker(void) {
        while (true) {
            pthread_mutex_lock(&mutexQueue);
            while (taskQueue.empty() && !shutdown)
                pthread_cond_wait(&condQueue, &mutexQueue);

            if (shutdown && taskQueue.empty()) {
                pthread_mutex_unlock(&mutexQueue);
                return;
            }

            Task* task = taskQueue.front(); 
            taskQueue.pop();
            pthread_mutex_unlock(&mutexQueue);

            task->taskFunction(task->args);

            pthread_mutex_lock(&mutexQueue);
            if (taskQueue.empty())
                pthread_cond_signal(&condDone);
            pthread_mutex_unlock(&mutexQueue);
        }
        return;
    }
    static void* worker_thread(void* args) {
        ThreadPool *pool = (ThreadPool*)(args);
        pool->worker();
        return NULL;
    }
public:
    void submitTask(Task *task) {
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
    ThreadPool(size_t numThreads): shutdown(false) {
        pthread_mutex_init(&mutexQueue, NULL);
        pthread_cond_init(&condQueue, NULL);
        pthread_cond_init(&condDone, NULL);

        threads.assign(numThreads, 0);
        for (size_t i = 0; i < numThreads; ++i) 
            pthread_create(&threads[i], NULL, 
                &ThreadPool::worker_thread, this);
    }
    ~ThreadPool() {
        pthread_mutex_lock(&mutexQueue);
        shutdown = true;
        pthread_mutex_unlock(&mutexQueue);

        pthread_cond_broadcast(&condQueue);
        for (pthread_t& th: threads) 
            pthread_join(th, NULL);
        
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

    string get_hostname(const string& url) {
        size_t start = url.find("://") + 3;
        size_t end = url.find('/', start);
        return url.substr(start, end - start);
    }

    void dfs(const string& currUrl) {
        string hostname = get_hostname(currUrl);
        vector<string> urls = htmlParser->getUrls(currUrl);

        for (const string& url: urls) {
            if (hostname != get_hostname(url)) continue;

            mutexVisited.lock();
            if (visited.count(url)) {
                mutexVisited.unlock();
                continue;
            }

            visited.insert(url);
            mutexVisited.unlock();

            UserArgs *uargs = new UserArgs();
            uargs->obj = this;
            uargs->arg = url;

            Task* task = new Task();
            task->taskFunction = &Solution::dfs_wrapper;
            task->args = uargs;
            threadPool->submitTask(task);
        }
    }

    static void dfs_wrapper(void *args) {
        UserArgs *uargs = (UserArgs*)(args);
        Solution *obj = uargs->obj;
        obj->dfs(uargs->arg);
    }

public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        this->htmlParser = &htmlParser;
        this->threadPool = new ThreadPool(256);

        visited.insert(startUrl);

        UserArgs *uargs = new UserArgs();
        uargs->obj = this;
        uargs->arg = startUrl;

        Task* task = new Task();
        task->taskFunction = &Solution::dfs_wrapper;
        task->args = uargs;
        threadPool->submitTask(task);

        threadPool->waitAll();
        delete threadPool;
        delete uargs;

        return vector<string>(visited.begin(), visited.end());
    }
};