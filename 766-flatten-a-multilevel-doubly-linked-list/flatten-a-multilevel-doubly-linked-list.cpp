/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

// #define DEBUG
#ifdef DEBUG
#define debug(x) cout << #x << " is " << x << endl;
#else
#define debug(x)
#endif

class Solution {
    Node* do_flatten(Node* head) {
        if (!head) return NULL;
        debug(head->val);
        Node* curr = head;
        while (curr) {
            // find branch
            for (; !curr->child; curr = curr->next)
                if (!curr->next) break;

            // stop when reached the end
            if (!curr->next) break;

            Node* next = curr->next;
            Node* child_end = do_flatten(curr->child);

            curr->next = curr->child;
            curr->child->prev = curr;
            child_end->next = next;
            next->prev = child_end;

            curr->child = NULL;
            curr = curr->next;
        }

        if (!curr->next && curr->child) {
            Node* child_end = do_flatten(curr->child);
            
            curr->next = curr->child;
            curr->child->prev = curr;
            child_end->next = NULL;
            curr->child = NULL;
        }

        // return the end
        for (; curr->next; curr = curr->next);
        return curr;
    }
public:
    Node* flatten(Node* head) {
        Node* ret = head;
        do_flatten(head);

        return ret;
    }
};