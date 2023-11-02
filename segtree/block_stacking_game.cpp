#include<vector>
#include<climits>

using namespace std;
using ll = long long;

const int MOD = 1e6;
const int MAX_N = 1e6;

struct Result {
    int top;
    int count;

    Result(int top, int count) : top(top), count(count) {};
};

struct Node {
    int max, min, lzAdd;
};

ll sum;
int column;
vector<Node> st(4 * MAX_N, Node());

int lc(int node) { return node << 1; }
int rc(int node) { return (node << 1) + 1; }

void pushUp(int node) {
    st[node].min = min(st[lc(node)].min, st[rc(node)].min);
    st[node].max = max(st[lc(node)].max, st[rc(node)].max);
}

void pushDown(int node, int l, int r, int m) {
    if (st[node].lzAdd == 0) return;

    // Push down value in lazy segment tree
    st[lc(node)].lzAdd += st[node].lzAdd;
    st[rc(node)].lzAdd += st[node].lzAdd;

    // Update value min
    st[lc(node)].min += st[node].lzAdd;
    st[rc(node)].min += st[node].lzAdd;

    // Update value max
    st[lc(node)].max += st[node].lzAdd;
    st[rc(node)].max += st[node].lzAdd;

    st[node].lzAdd = 0;
}

void updateUtil(int node, int l, int r, int ql, int qr, ll val) {
    if (ql > r || qr < l) return;
    if (ql <= l && qr >= r) {
        st[node].lzAdd += val;

        st[node].max += val;
        st[node].min += val;

        return;
    }

    int m = (l + r) / 2;

    pushDown(node, l, r, m);

    updateUtil(lc(node), l, m, ql, qr, val);
    updateUtil(rc(node), m + 1, r, ql, qr, val);

    pushUp(node);
}

void update(int ql, int qr, ll val) {
    return updateUtil(1, 0, column - 1, ql, qr, val);
}

void init(int C) {
    sum = 0;
    column = C;
    for(int i = 0; i < 4 * column; ++i)
        st[i].max = st[i].min = st[i].lzAdd = 0;
}

Result dropBlocks(int mCol, int mHeight, int mLength)
{
    update(mCol, mCol + mLength - 1, mHeight);

    sum += 1LL * mLength * mHeight;
    int minHeight = st[1].min, maxHeight = st[1].max;

    int top = maxHeight - minHeight;
    int totalBlock = static_cast<int>((sum - minHeight * column) % MOD);

    return Result(top, totalBlock);
}
