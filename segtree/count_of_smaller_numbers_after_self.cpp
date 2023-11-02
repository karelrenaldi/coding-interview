#include<vector>

using namespace std;

class NumArray {
public:
    int n;
    vector<int> arr, st;

    NumArray(vector<int>& nums) : n(nums.size()), st(4 * n, 0) {
        arr = nums;
        buildST(1, 0, n - 1);
    }

    void buildST(int node, int l, int r) {
        if (l == r) {
            st[node] = arr[l];
            return;
        }

        int m = (l + r) / 2;

        buildST(2 * node, l, m);
        buildST(2 * node + 1, m + 1, r);

        st[node] = st[2 * node] + st[2 * node + 1];
    }

    void update(int index, int val) {
        updateST(index, val, 1, 0, n - 1);
        arr[index] += val;
    }

    void updateST(int index, int val, int node, int l, int r) {
        if (l == r) {
            st[node] += val;
            return;
        }

        int m = (l + r) / 2;
        if (index <= m)
            updateST(index, val, 2 * node, l, m);
        else
            updateST(index, val, 2 * node + 1, m + 1, r);

        st[node] = st[2 * node] + st[2 * node + 1];
    }

    int sumRange(int left, int right) {
        return sumRangeUtil(1, 0, n - 1, left, right);
    }

    int sumRangeUtil(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l || ql > qr) return 0;
        if (ql <= l && qr >= r) return st[node];

        int m = (l + r) / 2;

        int sumRangeL = sumRangeUtil(2 * node, l, m, ql, qr);
        int sumRangeR = sumRangeUtil(2 * node + 1, m + 1, r, ql, qr);

        return sumRangeL + sumRangeR;
    }
};

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int min = nums[0], max = nums[0], n = nums.size();
        for(int i = 1; i < n; ++i) {
            if(nums[i] > max) max = nums[i];
            if(nums[i] < min) min = nums[i];
        }

        vector<int> arr(max - min + 1, 0);
        NumArray* obj = new NumArray(arr);

        vector<int> res(n, 0);
        for(int i = n - 1; i >= 0; --i) {
            int idxST = nums[i] - min;

            res[i] = obj->sumRange(0, idxST - 1);
            obj->update(idxST, 1);
        }

        return res;
    }
};