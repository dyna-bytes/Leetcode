// #define DEBUG
#ifdef DEBUG
#define debug(x) cout << "[" << __func__ << "]" << #x << " is " << x << endl;
#define debugSeq(s) do { \
    cout << "[" << __func__ << "]" << #s << " is |"; \
    for (auto e : s) cout << "{ " << e.first << ", " << e.second << " }|"; \
    cout << endl; \
} while (0)
#else
#define debug(x)
#define debugSeq(s)
#endif

typedef struct __node {
    int key;
    int val;
    struct __node *prev;
    struct __node *next;
} node;

class LRUCache {
    node* head;
    node* tail;
    node dummy_head = {-1, -1, NULL, NULL};
    node dummy_tail = {-1, -1, NULL, NULL};
    int size;
    int cap;
    unordered_map<int, node*> hash;

    void initList() {
        head = &dummy_head;
        tail = &dummy_tail;
        head->next = tail;
        tail->prev = head;
        size = 0;
    }
    void deleteNode(node* curr) {
        node* prev = curr->prev;
        node* next = curr->next;

        prev->next = next;
        next->prev = prev;
    }
    void insertLast(node* curr) {
        node* last = tail->prev;

        last->next = curr;
        curr->prev = last;

        curr->next = tail;
        tail->prev = curr;
    }
public:
    int getSize() { return size; }
    unordered_map<int, node*>* getHash() { return &hash; }
    LRUCache(int capacity=INT_MAX) {
        cap = capacity;
        initList();
    }
    void deleteNodeFromLRU(node* curr) {
        hash.erase(curr->key);
        deleteNode(curr);
        size--;
    }
    node* popFront() {
        assert(size != 0);
        if (size == 0) return NULL;
        node* front = head->next;
        deleteNodeFromLRU(front);
        return front;
    }
    node* getNodeWithoutCount(int key) {
        if (hash.count(key) == 0) return NULL;
        return hash[key];
    }
    
    int get(int key) {
        if (hash.count(key) == 0) return -1;

        node* curr = hash[key];

        deleteNode(curr);
        insertLast(curr);
        return curr->val;
    }
    
    void put(int key, int value) {
        if (get(key) != -1) {
            node* curr = hash[key];
            curr->val = value;
            return;
        }
        
        if (size >= cap) {
            hash.erase(head->next->key);
            deleteNode(head->next);
            size--;
        }

        node* curr = new node(key, value, NULL, NULL);
        hash[key] = curr;
        insertLast(curr);
        size++;
    }
};

class LFUCache {
    map<int, LRUCache*> freq; // {count : LRU list}
    unordered_map<int, int> counts; // {key : count} 
    int capacity;
    int size = 0;
public:
    LFUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        if (counts.find(key) == counts.end()) return -1;
        int cnt = counts[key];
        node* curr = freq[cnt]->getNodeWithoutCount(key);
        int val = curr->val;

        freq[cnt]->deleteNodeFromLRU(curr);
        if (freq[cnt]->getSize() == 0)
            freq.erase(cnt);

        counts[key] = ++cnt;

        if (freq.count(cnt) == 0)
            freq[cnt] = new LRUCache();

        freq[cnt]->put(key, val);
        return val;
    }
    
    void put(int key, int value) {
        if (get(key) != -1) {
            node* curr = freq[counts[key]]->getNodeWithoutCount(key);
            curr->val = value;
            return;
        }

        if (size >= capacity) {
            int LFU_count = freq.begin()->first;
            auto LFU_list = freq.begin()->second;
            node* LRU_node = LFU_list->popFront();
            int LRU_key = LRU_node->key;
            
            if (LFU_list->getSize() == 0)
                freq.erase(freq.begin());
            counts.erase(LRU_key);

            size--;
        }

        int cnt = 1;
        counts[key] = cnt;
        if (freq.count(cnt) == 0)
            freq[cnt] = new LRUCache();
        freq[cnt]->put(key, value);
        size++;
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */