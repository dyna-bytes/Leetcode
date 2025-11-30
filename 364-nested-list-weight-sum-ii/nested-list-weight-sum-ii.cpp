/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

#define debug(x) cout << #x << " is " << x << endl;
class Solution {
    int get_max_depth(NestedInteger& curr) {
        if (curr.isInteger()) {
            return 0;
        }

        int max_depth = 0;
        for (NestedInteger& ni: curr.getList()) 
            max_depth = max(max_depth, 1 + get_max_depth(ni));
        return max_depth;
    }
    int get_weight_mul_val_sum(NestedInteger& curr, int depth, int max_depth) {
        if (curr.isInteger()) {
            int weight = max_depth - depth + 1;
            return curr.getInteger() * weight;
        }

        int weight_mul_val_sum = 0;
        for (NestedInteger& ni: curr.getList())
            weight_mul_val_sum += get_weight_mul_val_sum(ni, depth + 1, max_depth);
        return weight_mul_val_sum;
    }
public:
    int depthSumInverse(vector<NestedInteger>& nestedList) {
        int max_depth = 0;
        for (NestedInteger& ni: nestedList) 
            max_depth = max(max_depth, 1 + get_max_depth(ni));
        
        // debug(max_depth);
        int weight_mul_val_sum = 0;
        for (NestedInteger& ni: nestedList)
            weight_mul_val_sum += get_weight_mul_val_sum(ni, 1, max_depth);
        return weight_mul_val_sum;
    }
};