#include<queue>
#include<vector>

#define pii std::pair<int, int>
#define MAX_N 50

const int dr[4] = {-1, 0, 1, 0};
const int dc[4] = {0, 1, 0, -1};

class Solution {
public:
    int R, C;

    int visited = 1;
    int visit[MAX_N][MAX_N];

    int maxAreaOfIsland(std::vector<std::vector<int>>& grid) {
        R = grid.size(), C = grid[0].size();

        int maxIsland = 0;
        for(int row = 0; row < R; row++) {
            for(int col = 0; col < C; col++) {
                if(visit[row][col] == visited || grid[row][col] == 0)
                    continue;

                maxIsland = std::max(maxIsland, bfs(grid, row, col));
            }
        }

        return maxIsland;
    }

    int bfs(std::vector<std::vector<int>>& grid, int row, int col) {
        int res = 1;

        std::queue<pii> q;
        q.push({ row, col });

        visit[row][col] = visited;

        while(!q.empty()) {
            pii pos = q.front();
            q.pop();

            for(int i = 0; i < 4; i++) {
                int newR = pos.first + dr[i];
                int newC = pos.second + dc[i];

                if(newR < 0 || newR >= R) continue;
                if(newC < 0 || newC >= C) continue;
                if(grid[newR][newC] == 0) continue;
                if(visit[newR][newC] == visited) continue;

                res++;
                
                q.push({ newR, newC });
                visit[newR][newC] = visited;
            }
        }

        return res;
    }
};