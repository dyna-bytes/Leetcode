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
    bool isPalindrome(ListNode* head) {
        int n = 0;
        for (auto curr = head; curr; curr = curr->next)
            n++;

        stack<int> st;
        auto half = head;
        for (int i = 0; i < n/2; half = half->next) {
            st.push(half->val);
            i++;
        }

        if (n & 1) half = half->next;
        for (auto curr = half; curr; curr = curr->next) {
            if (st.top() != curr->val) return false;
            st.pop();
        }
        return true;
    }
};