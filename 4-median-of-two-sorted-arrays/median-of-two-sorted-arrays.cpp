#define debug(x) cout << #x << " is " << x << endl;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();

        if (m == 0) {
            if (n & 1)
                return nums2[n / 2];
            return (double)(nums2[n / 2 - 1] + nums2[n / 2]) / 2;
        }
        if (n == 0) {
            if (m & 1)
                return nums1[m / 2];
            return (double)(nums1[m / 2 - 1] + nums1[m / 2]) / 2;
        }

        if (m > n) return findMedianSortedArrays(nums2, nums1);

        /*
        nums1 = L1 + R1
        nums2 = L2 + R2

        if {L1, L2} < {R1, R2},
        then {L1, L2} + {R1, R2} would be sorted.

        To meet {L1, L2} < {R1, R2},
        max(L1, L2) < min(R1, R2)

        Which means,
        maxL1 < minR2 & maxL2 < minR1.

        Because
        maxL1 < maxR1 & maxL2 < maxR2 are already met.

        L1 = nums1[ :i-1], R1 = nums1[i: ]
        L2 = nums2[ :j-1], R2 = nums2[j: ]

        with constraint (i + j) = (m + n)/2.
        This constraint makes size({L1, L2}) == size({R1, R2}).
        */

        int i, j;
        int lo = 0, hi = m;
        while (true) {
            i = (lo + hi) / 2;
            j = (m + n) / 2 - i;

            int maxL1 = i == 0 ? INT_MIN : nums1[i - 1];
            int maxL2 = j == 0 ? INT_MIN : nums2[j - 1];
            int minR1 = i == m ? INT_MAX : nums1[i];
            int minR2 = j == n ? INT_MAX : nums2[j];

            if (maxL1 > minR2) {
                hi = i - 1; // lowering i
            } else if (maxL2 > minR1) {
                lo = i + 1; // highering i
            } else if (maxL1 <= minR2 && maxL2 <= minR1) {
                if ((m + n) & 1) 
                    return min(minR1, minR2);
                return (double)(max(maxL1, maxL2) + min(minR1, minR2)) / 2;
            }
        }
        return 0;
    }
};