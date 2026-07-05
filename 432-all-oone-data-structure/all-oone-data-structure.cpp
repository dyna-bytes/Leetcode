class AllOne {
    #define debug(x) cout << "[" << __func__ << "](" << __LINE__ << ") " << #x << " is " << x << endl;
    typedef struct node_t {
        struct node_t* prev;
        struct node_t* next;
        int cnt;
        unordered_set<string> keys;
    } Node;

    Node* head;
    Node* tail;
    unordered_map<string, Node*> hash;

    void insertNode(Node* node, Node* prev) {
        Node* next = prev->next;

        prev->next = node;
        node->prev = prev;

        next->prev = node;
        node->next = next;
    }
    void removeNode(Node* node) {
        Node* prev = node->prev;
        Node* next = node->next;

        prev->next = next;
        next->prev = prev;
    }
public:
    AllOne() {
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }
    
    void inc(string key) {
        Node* curr = hash.count(key) ? hash[key] : head;

        int x = curr->cnt;

        if (curr->next != tail && curr->next->cnt == x + 1) {
            curr->next->keys.insert(key);
            hash[key] = curr->next;
        } else {
            Node* node = new Node();
            node->cnt = x + 1;
            node->keys = { key };

            insertNode(node, curr);
            hash[key] = node;
        }

        if (curr == head) return;

        curr->keys.erase(key);
        if (curr->keys.empty()) {
            removeNode(curr);
            delete curr;
        }
    }
    
    void dec(string key) {
        Node* curr = hash[key];
        int x = curr->cnt;

        if (x == 1) {
            hash.erase(key);
            curr->keys.erase(key);
            if (curr->keys.empty()) {
                removeNode(curr);
                delete curr;
            }
            return;
        }

        if (curr->prev != head && curr->prev->cnt == x - 1) {
            curr->prev->keys.insert(key);
            hash[key] = curr->prev;
        } else {
            Node* node = new Node();
            node->cnt = x - 1;
            node->keys = { key };

            insertNode(node, curr->prev);
            hash[key] = node;
        }

        curr->keys.erase(key);
        if (curr->keys.empty()) {
            removeNode(curr);
            delete curr;
        }
    }
    
    string getMaxKey() {
        Node* curr = tail->prev;
        if (curr == head) return "";
        return *curr->keys.begin();
    }
    
    string getMinKey() {
        Node* curr = head->next;
        if (curr == tail) return "";
        return *curr->keys.begin();   
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */