/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* ret = head;

        ListNode *curr, *next, *prev = NULL;
        ListNode *dup;
        for (curr = head; curr; curr = next) {
            int cnt = 0;
            for (dup = curr; dup && dup->val == curr->val; dup = dup->next)
                cnt++;

            next = dup;
            if (cnt > 1) {
                if (prev) 
                    prev->next = next;
                else 
                    ret = next;
                continue;
            }
            prev = curr;
        }

        return ret;
    }
};