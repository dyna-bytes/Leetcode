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

class LRUCache {
    typedef struct __node {
        int key;
        int val;
        struct __node *prev;
        struct __node *next;
    } node;

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
    LRUCache(int capacity) {
        cap = capacity;
        initList();
    }
    
    int get(int key) {
        if (hash.count(key) == 0) return -1;

        node* curr = hash[key];

        deleteNode(curr);
        insertLast(curr);
        debugSeq(hash);
        return curr->val;
    }
    
    void put(int key, int value) {
        if (get(key) != -1) {
            node* curr = hash[key];
            curr->val = value;
            debugSeq(hash);
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
        debugSeq(hash);
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */