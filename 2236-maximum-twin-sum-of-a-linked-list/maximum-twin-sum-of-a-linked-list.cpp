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
    int pairSum(ListNode* head) {
        unordered_map<int, int> um;

        int i = 0;
        for (ListNode* curr = head; curr; curr = curr->next) {
            um[i] = curr->val;
            i++;
        }
        
        int n = i;
        int ret = 0;
        for (int j = 0; j < n/2; j++)
            ret = max(ret, um[j] + um[n-1-j]);
        return ret;
    }
};