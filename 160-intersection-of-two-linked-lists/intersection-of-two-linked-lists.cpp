/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode*> us;
        for (auto curr = headA; curr; curr = curr->next)
            us.insert(curr);

        for (auto curr = headB; curr; curr = curr->next)
            if (us.count(curr)) return curr;

        return NULL;
    }
};