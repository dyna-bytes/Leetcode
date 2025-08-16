class Solution {
    int N;
    unordered_set<int> total_ors;
    unordered_set<int> current_ors; // arr[i] 로 끝나는 서브배열들의 or 값
    unordered_set<int> previous_ors; // arr[i-1] 로 끝나는 서브배열들의 or 값

public:
    int subarrayBitwiseORs(vector<int>& arr) {
        N = arr.size();
        for (int i = 0; i < N; i++) {
            previous_ors = current_ors;
            current_ors.clear();

            current_ors.insert(arr[i]);
            for (auto p: previous_ors) 
                current_ors.insert(p | arr[i]);

            total_ors.insert(current_ors.begin(), current_ors.end());
        }

        return total_ors.size();
    }
};