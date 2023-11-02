#include<queue>
#include<vector>

using namespace std;

#define pii pair<int, int>

class Solution {
public:
    const int dr[4] = {-1, 0, 1, 0};
    const int dc[4] = {0, 1, 0, -1};

    int R, C;
    int visited;

    vector<vector<int>> grid, visit;
    vector<vector<bool>> isPacific, isAtlantic;

    void bfs(queue<pii>& q, vector<vector<bool>>& mark) {
        while(!q.empty()) {
            pii curr = q.front();
            q.pop();

            int currR = curr.first, currC = curr.second;
            for(int i = 0; i < 4; ++i) {
                int newR = currR + dr[i], newC = currC + dc[i];
                
                if(newR < 0 || newR >= R) continue;
                if(newC < 0 || newC >= C) continue;
                if(visit[newR][newC] == visited) continue;
                if(grid[newR][newC] < grid[currR][currC]) continue;

                q.push({ newR, newC });
                mark[newR][newC] = true;
                visit[newR][newC] = visited;
            }
        }
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        grid = heights;

        R = grid.size(), C = grid[0].size();

        visit.assign(R, vector<int>(C, 0));

        vector<vector<bool>> isPacific(R, vector<bool>(C, false));
        vector<vector<bool>> isAtlantic(R, vector<bool>(C, false));

        queue<pii> pacificQ, atlanticQ;

        for(int i = 0; i < R; ++i)
            for(int j = 0; j < C; ++j) {
                if(i == 0 || j == 0) {
                    isPacific[i][j] = true;
                    visit[i][j] = 1;
                    pacificQ.push({ i, j });
                }

                if(i == R - 1 || j == C - 1) {
                    isAtlantic[i][j] = true;
                    visit[i][j] = 2;
                    atlanticQ.push({ i, j });
                }
            }

        visited = 1;
        bfs(pacificQ, isPacific);
        visited = 2;
        bfs(atlanticQ, isAtlantic);

        vector<vector<int>> res;
        for(int i = 0; i < R; ++i)
            for(int j = 0; j < C; ++j)
                if(isPacific[i][j] && isAtlantic[i][j])
                    res.push_back({ i, j });

        return res;
    }
};
