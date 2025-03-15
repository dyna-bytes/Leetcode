class Solution {
    typedef long long ll;
    vector<int> slots;
    #define MAX_SLOT 15
    int dp[2*MAX_SLOT + 1][60000];
    ll pow3[MAX_SLOT + 1];
    void initPow3() {
        pow3[0] = 1;
        for (int i = 1; i <= MAX_SLOT; i++)
            pow3[i] = pow3[i - 1] * 3LL;
    }

    ll getSlotUsage(ll state, int pos) {
        ll div = state / pow3[pos-1];
        return div % 3LL;
    }

    ll setSlotUsage(ll state, int pos, ll newUsage) {
        ll oldUsage = getSlotUsage(state, pos);
        ll diff = newUsage - oldUsage;
        return state + diff * pow3[pos-1];
    }

    int findMaxANDSum(int curr, ll state, vector<int>& nums, int numSlots) {
        if (curr == nums.size())
            return 0;

        int& ret = dp[curr][state];
        if (ret != -1) return ret;

        for (int slot = 1; slot <= numSlots; slot++) {
            ll usage = getSlotUsage(state, slot);
            if (usage < 2) {
                ll newState = setSlotUsage(state, slot, usage + 1);

                ret = max(ret,
                    (nums[curr] & slot) + findMaxANDSum(curr+1, newState, nums, numSlots));
            }
        }
        
        return ret;
    }

public:
    int maximumANDSum(vector<int>& nums, int numSlots) {
        slots.resize(numSlots + 1, 0);
        memset(dp, -1, sizeof(dp));
        sort(nums.begin(), nums.end());
        initPow3();
        return findMaxANDSum(0, 0, nums, numSlots);
    }
};