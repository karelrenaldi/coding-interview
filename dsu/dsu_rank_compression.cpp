#include <iostream>

#define N 5

int parent[N], rank[N];

void init() {
    for(int i = 0; i < N; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
}

// Find using path compression
int find(int x) {
    if(parent[x] == x)
        return x;

    parent[x] = find(parent[x]);
    
    return parent[x];
}

// Union by rank
void join(int x, int y) {
    int px = find(x);
    int py = find(y);

    if(px == py) 
        return;
    
    if(rank[px] < rank[py]) parent[px] = py;
    else if(rank[px] > rank[py]) parent[py] = px;
    else {
        parent[py] = px;
        rank[px]++;
    }
}
