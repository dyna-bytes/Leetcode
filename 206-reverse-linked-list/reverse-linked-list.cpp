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
#define debug(x) cout << #x << " is " << x << endl;
class Solution {
    ListNode* reverse(ListNode* curr, ListNode* prev) {
        if (!curr) return NULL;

        ListNode* next = curr->next;
        curr->next = prev;

        auto ret = reverse(next, curr);
        if (!ret) return curr;
        return ret;
    }
public:
    ListNode* reverseList(ListNode* head) {
        if (!head) return NULL;

        return reverse(head, NULL);
    }
};