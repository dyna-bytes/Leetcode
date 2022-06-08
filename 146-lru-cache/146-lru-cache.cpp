
class LRUCache{
public:
    struct Node{
        int key, value;
        Node* prev, * next;
        Node(int k, int v){
            key = k, value = v;
            prev = next = nullptr;
        }
    };

    int cap;
    Node* head;// = new node(-1, -1);
    Node* tail;// = new node(-1, -1);
    unordered_map<int, Node*> map;

    LRUCache(int capacity){
        cap = capacity;
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key){
        auto ret = map.find(key);
        if(ret == map.end()) return -1;

        Node* node = ret->second;
        deleteNode(node);
        insertBack(node);

        // debugLRU();
        return node->value;
    }

    void put(int key, int value){
        if(get(key) != -1){
            map.find(key)->second->value = value;
            return;
        }
        
        Node* node = new Node(key, value);
        insertBack(node);
        map.insert({key, node});

        if(map.size() > cap){            
            Node* head_back = head->next;
            map.erase(head_back->key);
            deleteNode(head_back);
            delete head_back;
        }

        // debugLRU();
    }
private:
    void debugLRU(){
        for(Node* n = head; n != tail; n = n->next)
            cout << "(" << n->key << ", " << n->value << ") -> ";
        cout << "(" << tail->key << ", " << tail->value << ")" << endl;
    }

    void insertBack(Node* node){
        Node* tail_front = tail->prev;
        node->prev = tail_front;
        node->next = tail;

        tail_front->next = node;
        tail->prev = node;
    }
    void deleteNode(Node* node){
        Node* node_front = node->prev;
        Node* node_back = node->next;

        node_front->next = node_back;
        node_back->prev = node_front;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */