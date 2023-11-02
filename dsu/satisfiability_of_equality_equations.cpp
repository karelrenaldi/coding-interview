#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int parent[26], rank[26];

    int find(int x) {
        if(parent[x] == x) return x;

        parent[x] = find(parent[x]);
        return parent[x];
    }

    void join(int x, int y) {
        int xRep = find(x);
        int yRep = find(y);
        if(xRep == yRep) return;

        if(rank[xRep] < rank[yRep]) parent[xRep] = yRep;
        else if(rank[yRep] < rank[xRep]) parent[yRep] = xRep;
        else {
            parent[yRep] = xRep;
            rank[xRep]++;
        }
    }

    bool equationsPossible(vector<string>& equations) {
        for(int i = 0; i < 26; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }

        for(const string& eq: equations) {
            if(eq[1] == '!') continue;

            join(eq[0] - 'a', eq[3] - 'a');
        }

        for(const string& eq: equations) {
            if(eq[1] == '=') continue;

            int xRep = find(eq[0] - 'a');
            int yRep = find(eq[3] - 'a');

            if(xRep == yRep) return false;
        }

        return true;
    }
};
