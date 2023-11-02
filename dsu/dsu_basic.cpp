#include <iostream>

#define N 5

int parent[N];

void init() {
    for(int i = 0; i < N; ++i)
        parent[i] = i;
}

int find(int x) {
    return parent[x] == x ? x : find(parent[x]);
}

void join(int x, int y) {
    int px = find(x);
    int py = find(y);

    if(px == py) 
        return;
        
    parent[py] = px;
}
