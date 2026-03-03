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

// Solution 객체 포인터를 포함하여 전달하도록 수정
struct UserArgs {
    Solution* obj;
    string arg;
};

// 일반 함수 포인터로 변경
struct Task {
    void (*taskFunction)(void *);
    void *args;
};

class ThreadPool {
private:
    vector<pthread_t> threads;
    queue<Task*> taskQueue;
    pthread_mutex_t mutexQueue;
    pthread_cond_t condQueue;
    pthread_cond_t condDone; // 작업이 모두 끝났음을 알리는 조건 변수
    
    bool shutdown;
    int activeTasks; // 현재 실행 중인 작업 수 추적

    void workerLoop() {
        while (true) {
            pthread_mutex_lock(&mutexQueue);
            
            while (taskQueue.empty() && !shutdown) {
                pthread_cond_wait(&condQueue, &mutexQueue);
            }
            
            if (shutdown && taskQueue.empty()) {
                pthread_mutex_unlock(&mutexQueue);
                return;
            }
            
            Task* task = taskQueue.front();
            taskQueue.pop();
            activeTasks++; // 작업 시작
            
            pthread_mutex_unlock(&mutexQueue);
            
            // 작업 실행
            if (task && task->taskFunction) {
                task->taskFunction(task->args);
            }
            
            // 동적 할당된 메모리 해제
            delete static_cast<UserArgs*>(task->args);
            delete task;
            
            // 작업 완료 처리
            pthread_mutex_lock(&mutexQueue);
            activeTasks--;
            // 큐가 비어있고, 일하는 스레드도 없다면 모든 크롤링이 끝난 것
            if (taskQueue.empty() && activeTasks == 0) {
                pthread_cond_signal(&condDone);
            }
            pthread_mutex_unlock(&mutexQueue);
        }
    }

    static void* startThread(void* arg) {
        ThreadPool* pool = (ThreadPool*)(arg);
        pool->workerLoop();
        return nullptr;
    }

public:
    ThreadPool(size_t numThreads) : shutdown(false), activeTasks(0) {
        pthread_mutex_init(&mutexQueue, nullptr);
        pthread_cond_init(&condQueue, nullptr);
        pthread_cond_init(&condDone, nullptr);
        
        threads.resize(numThreads);
        for (size_t i = 0; i < numThreads; ++i) {
            if (pthread_create(&threads[i], nullptr, &ThreadPool::startThread, this) != 0) {
                perror("Failed to create the thread");
            }
        }
    }

    ~ThreadPool() {
        pthread_mutex_lock(&mutexQueue);
        shutdown = true;
        pthread_mutex_unlock(&mutexQueue);
        
        pthread_cond_broadcast(&condQueue);
        
        for (pthread_t& th : threads) {
            pthread_join(th, nullptr);
        }
        
        pthread_mutex_destroy(&mutexQueue);
        pthread_cond_destroy(&condQueue);
        pthread_cond_destroy(&condDone);
    }

    void submitTask(Task* task) {
        pthread_mutex_lock(&mutexQueue);
        taskQueue.push(task);
        pthread_mutex_unlock(&mutexQueue);
        pthread_cond_signal(&condQueue);
    }

    // 메인 스레드가 크롤링 완료를 기다리게 하는 함수
    void waitAll() {
        pthread_mutex_lock(&mutexQueue);
        while (!taskQueue.empty() || activeTasks > 0) {
            pthread_cond_wait(&condDone, &mutexQueue);
        }
        pthread_mutex_unlock(&mutexQueue);
    }
};

class Solution {
    unordered_set<string> visited;
    mutex m_visited;
    
    HtmlParser *htmlParser;
    ThreadPool *threadPool;

    string get_hostname(const string& url) {
        size_t start = url.find("://") + 3;
        size_t end = url.find('/', start);
        return url.substr(start, end - start);
    }

    static void dfs_wrapper(void *args) {
        UserArgs* uargs = (UserArgs*)(args);
        Solution* obj = uargs->obj;
        obj->dfs(uargs->arg);
    }

    void dfs(string currUrl) {
        string hostname = get_hostname(currUrl);
        vector<string> urls = htmlParser->getUrls(currUrl);

        for (const string& url: urls) {
            if (hostname != get_hostname(url)) continue;
            
            bool is_new = false;
            {
                lock_guard<mutex> v_lock(m_visited);
                if (visited.count(url) == 0) {
                    visited.insert(url);
                    is_new = true;
                }
            }
            
            if (is_new) {
                UserArgs* ua = new UserArgs();
                ua->obj = this;     // Solution 객체 주소 전달
                ua->arg = url;
                
                Task* t = new Task();
                t->taskFunction = &Solution::dfs_wrapper;
                t->args = ua;
                threadPool->submitTask(t);
            }
        }
    }
public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        this->htmlParser = &htmlParser;
        this->threadPool = new ThreadPool(256);

        visited.insert(startUrl);

        UserArgs* ua = new UserArgs();
        ua->obj = this;
        ua->arg = startUrl;
        
        Task* t = new Task();
        t->taskFunction = &Solution::dfs_wrapper;
        t->args = ua;
        threadPool->submitTask(t);
        
        threadPool->waitAll(); 
        delete threadPool;
        
        return vector<string>(visited.begin(), visited.end());
    }
};