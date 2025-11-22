#define debug(x) cout << #x << " is " << x << endl;

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [](int l, int r){
            string left = to_string(l);
            string right = to_string(r);
            
            return (left + right) > (right + left);
        });
        // if a.b > b.a && b.c > c.b,
        // then a.c > c.a
        // Transitive and Associative

        string ans;
        if (nums.size() && nums.front() == 0) return "0";
        for (int num: nums) ans.append(to_string(num));
        return ans;
    }
};