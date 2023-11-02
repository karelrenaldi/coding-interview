#include<vector>
#include<climits>

using namespace std;
using ll = long long;

struct SegmentTreeNode
{
    ll sum, min, max;
    ll lzAdd;

    SegmentTreeNode() {};
};

struct QueryResult
{
    ll sum, min, max;

    QueryResult() : sum(0), min(LLONG_MAX), max(LLONG_MIN) {};
    QueryResult(ll sum, ll min, ll max) : sum(sum), min(min), max(max) {};
};

class LazySegmentTree {
    int n;
    vector<int> arr;
    vector<SegmentTreeNode> st;
private:
    // Get left child index
    int lc(int node) { return node << 1; }

    // Get right child index
    int rc(int node) { return (node << 1) + 1; }

    void pushUp(int node) {
        st[node].sum = st[lc(node)].sum + st[rc(node)].sum;
        st[node].min = min(st[lc(node)].min, st[rc(node)].min);
        st[node].max = max(st[lc(node)].max, st[rc(node)].max);
    }

    void pushDown(int node, int l, int r, int m) {
        if(st[node].lzAdd == 0) return;

        // Push down value in lazy segment tree
        st[lc(node)].lzAdd += st[node].lzAdd;
        st[rc(node)].lzAdd += st[node].lzAdd;

        // Update value sum
        st[lc(node)].sum += (m - l + 1) * st[node].lzAdd;
        st[rc(node)].sum += (r - (m + 1) + 1) * st[node].lzAdd;

        // Update value min
        st[lc(node)].min += st[node].lzAdd;
        st[rc(node)].min += st[node].lzAdd;

        // Update value max
        st[lc(node)].max += st[node].lzAdd;
        st[rc(node)].max += st[node].lzAdd;

        st[node].lzAdd = 0;
    }

    QueryResult queryUtil(int node, int l, int r, int ql, int qr) {
        if(ql > r || qr < l) return QueryResult();
        if(ql <= l && qr >= r)
            return QueryResult(st[node].sum, st[node].min, st[node].max);

        int m = (l + r) / 2;

        pushDown(node, l, r, m);

        QueryResult lcRes = queryUtil(lc(node), l, m, ql, qr);
        QueryResult rcRes = queryUtil(rc(node), m + 1, r, ql, qr);
        
        ll newSum = lcRes.sum + rcRes.sum;
        ll newMin = min(lcRes.min, rcRes.min);
        ll newMax = max(lcRes.max, rcRes.max);

        return QueryResult(newSum, newMin, newMax);
    }

    void updateUtil(int node, int l, int r, int ql, int qr, ll val) {
        if(ql > r || qr < l) return;
        if(ql <= l && qr >= r) {
            st[node].sum += ((r - l + 1) * val);
            st[node].max += val;
            st[node].min += val;

            st[node].lzAdd += val;

            return;
        }

        int m = (l + r) / 2;

        pushDown(node, l, r, m);

        updateUtil(lc(node), l, m, ql, qr, val);
        updateUtil(rc(node), m + 1, r, ql, qr, val);

        pushUp(node);
    }

public:
    LazySegmentTree(vector<int>& nums) : n(nums.size()), st(4 * n, SegmentTreeNode()) {
        arr = nums;
        build(1, 0, n - 1);
    }

    void build(int node, int l, int r) {
        st[node].lzAdd = 0;

        if(l == r) {
            st[node].sum = arr[l];
            st[node].min = arr[l];
            st[node].max = arr[l];

            return;
        }

        int m = (l + r) / 2;

        build(lc(node), l, m);
        build(rc(node), m + 1, r);

        pushUp(node);
    }

    void update(int ql, int qr, ll val) {
        return updateUtil(1, 0, n - 1, ql, qr, val);
    }

    QueryResult query(int ql, int qr) {
        return queryUtil(1, 0, n - 1, ql, qr);
    }
};
