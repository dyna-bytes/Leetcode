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
    void deleteNode(ListNode* node) {
        auto curr = node, prev = node;
        for (; curr->next; curr = curr->next) {
            curr->val = curr->next->val;
            prev = curr;
        }
        prev->next = NULL;
    }
};