// Segment Tree Implementation for Range Sum Query.

#include<vector>
#include<iostream>

using namespace std;

class NumArray {
public:
    int n;
    vector<int> arr, st;

    NumArray(vector<int>& nums) : n(nums.size()), st(4 * nums.size(), 0) {
        arr = nums;
        buildST(0, 0, n - 1);
    }

    void buildST(int node, int l, int r) {
        if(l == r) {
            st[node] = arr[l];
            return;
        }

        int m = (l + r) / 2;

        buildST(2*node + 1, l, m);
        buildST(2*node + 2, m + 1, r);

        st[node] = st[2*node + 1] + st[2*node + 2];
    }
    
    void update(int index, int val) {
        updateST(0, 0, n - 1, index, val);
        arr[index] = val;
    }

    void updateST(int node, int l, int r, int index, int val) {
        if(l == r) {
            st[node] = val;
            return;
        }

        int m = (l + r) / 2;

        if(index <= m)
            updateST(2*node + 1, l, m, index, val);
        else
            updateST(2*node + 2, m + 1, r, index, val);

        st[node] = st[2*node + 1] + st[2*node + 2];
    }
    
    int sumRange(int ql, int qr) {
        return sumRangeHelper(0, 0, n - 1, ql, qr);
    }

    int sumRangeHelper(int node, int l, int r, int ql, int qr) {
        if(ql > r || qr < l) return 0;
        if(ql <= l && qr >= r) return st[node];

        int m = (l + r) / 2;

        int resL = sumRangeHelper(2*node + 1, l, m, ql, qr);
        int resR = sumRangeHelper(2*node + 2, m + 1, r, ql, qr);

        return resL + resR;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */