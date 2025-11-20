/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#define debug(x) cout << #x << " is " << x << endl;
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (!head) return false;
        
        auto t = head, h = head;
        do {
            t = t->next;
            h = h->next;
            if (!h) return false;
            h = h->next;
            if (!h) return false;
        } while (t != h);

        return true;
    }
};