#include <vector>

using std::vector;

class Solution {
public:
    virtual int maxSubArray(vector<int>&) = 0;
};

// Dynamic Programming
class Solution1 : public Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int pre = 0, maxAns = nums[0];
        for (const auto &x : nums) {
            pre = std::max(pre + x, x);
            maxAns = std::max(maxAns, pre);
        }
        return maxAns;
    }
};

// Divide and Conquer
class Solution2 : public Solution {
private:
    struct Status {
        int lSum, rSum, mSum, iSum;
    };

    Status pushUp(Status& l, Status& r) {
        int iSum = l.iSum + r.iSum;
        int lSum = std::max(l.lSum, l.iSum + r.lSum);
        int rSum = std::max(r.rSum, r.iSum + l.rSum);
        int mSum = std::max(std::max(l.mSum, r.mSum), l.rSum + r.lSum);
        return (Status) {lSum, rSum, mSum, iSum};
    }

    Status get(vector<int>& a, int l, int r) {
        if (l == r) return (Status) {a[l], a[l], a[l], a[l]};
        int m = (l + r) >> 1;
        Status lSub = get(a, l, m);
        Status rSub = get(a, m + 1, r);
        return pushUp(lSub, rSub);
    }

public:
    int maxSubArray(vector<int>& nums) {
        return get(nums, 0, nums.size() - 1).mSum;
    }
};