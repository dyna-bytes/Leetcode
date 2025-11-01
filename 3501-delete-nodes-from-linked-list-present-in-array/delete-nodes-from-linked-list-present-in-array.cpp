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
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        unordered_set<int> us(nums.begin(), nums.end());

        ListNode* curr, *ret = head;
        ListNode* prev = NULL, *next = NULL;
        for (curr = head; curr; curr = curr->next) {
            if (us.count(curr->val) == 0) {
                prev = curr;
                continue;
            }

            next = curr->next;
            if (prev) 
                prev->next = next;

            if (ret == curr) 
                ret = next;
        }
        return ret;
    }
};