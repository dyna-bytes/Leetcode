class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        if(n == 1) return (nums[0] == target)? 0 : -1;

        return findTargetIdx(0, nums.size()-1, nums, target);
    }
    
    // rotated sorted array는 두 개의 오름차순 정렬된 배열로 이루어져 있다.
    // 전체 배열이 두 개의 오름차순 배열로 이루어져 있다고 하자.
    // 즉, A = [[A1], [A2]]. 이때 A1 > A2 이다.
    
    // case1. A1.back() < target                --> return -1
    // case2. A1.front() <= target <= A1.back()
    // case3. A2.back() < target < A1.front()   --> return -1
    // case4. A2.front() <= target <= A2.back()
    // case5. target < A2.front()               --> return -1
    
    // 절대 불가능한 1, 3, 5번 케이스는 제외하고
    // 2, 4번 케이스는 하나의 정렬된 어레이에서 원하는 값을 찾는 문제이다.
    // stl lower_bound를 쓰든 직접 구현하든 알아서 하면 된다.
    
    int findTargetIdx(int s, int e, vector<int>& nums, int target){
        if(s == e) {
            if(nums[s] == target) return s;
            else return -1;
        }
        if(s + 1 == e) {
            if(nums[s] == target) return s;
            else if(nums[e] == target) return e;
            else return -1;
        }
        
        if(nums[s] > nums[e]){
            int mid = (s + e)/2;
            if(nums[mid] > nums[s]){
                if(target == nums[mid]){ return mid; }
                return max(findTargetIdx(s, mid, nums, target), findTargetIdx(mid, e, nums, target));
            }
            else {
                if(target == nums[mid]){ return mid; }
                return max(findTargetIdx(s, mid, nums, target), findTargetIdx(mid, e, nums, target));
            }
        }
        else{
            e = (e + 1 >= nums.size())? nums.size() : e + 1;
            while(s + 1 < e){
                int mid = (s + e)/2;
                if(target == nums[mid]) return mid;
                else if(target < nums[mid]) e = mid;
                else s = mid;
            }
            if(target == nums[s]) return s;
            else return -1;
        }
        
        
    }
};