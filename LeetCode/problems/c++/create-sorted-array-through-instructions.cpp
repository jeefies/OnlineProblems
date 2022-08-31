const int MAX_I = 1e5;
const int MAX_R = 1e9 + 7;
// 利用树状数组解决
class BIT {
    // Binary Index Tree
public:
    int nums[MAX_I + 1] = {0};

    int lowbit(int i) {
        return i & -i;
    }

    void update(int i, int k) {
        while (i < MAX_I) {
            nums[i] += k;
            i += lowbit(i);
        }
    }

    int getsum(int i) {
        int ans = 0;
        while (i) {
            ans += nums[i];
            i -= lowbit(i);
        }
        return ans;
    }
};

class Solution {
public:
    int min(int a, int b) {
        return a < b ? a : b;
    }
    
	int createSortedArray(vector<int>& instructions) {
        int cost = 0;
        BIT bit;
        for (int i = 0; i < instructions.size(); i++) {
            int ni = instructions[i];
            bit.update(ni, 1);
            int left = bit.getsum(ni - 1);
            int right = i+1 - bit.getsum(ni);
            cost = (min(left, right) + cost) % MAX_R;
        }
        return cost;
    }
};
