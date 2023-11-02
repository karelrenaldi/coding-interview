#include<queue>
#include<vector>

using namespace std;

#define pii pair<int, int>

class Solution {
public:
    const int dr[4] = {-1, 0, 1, 0};
    const int dc[4] = {0, 1, 0, -1};

    int orangesRotting(vector<vector<int>>& grid) {
        int R = grid.size(), C = grid[0].size();

        vector<vector<bool>> visit(R, vector<bool>(C, false));

        queue<pair<pii, int>> q;
        int totalFreshOrange = 0;

        for(int r = 0; r < R; ++r) {
            for(int c = 0; c < C; ++c) {
                if(grid[r][c] == 1) totalFreshOrange++;
                else if(grid[r][c] == 2) q.push({{ r, c }, 0});
            }
        }

        int day = 0;
        while(!q.empty()) {
            pair<pii, int> curr = q.front();
            q.pop();

            int currR = curr.first.first, currC = curr.first.second;
            int currDay = curr.second;

            day = max(day, currDay);

            for(int i = 0; i < 4; ++i) {
                int newR = currR + dr[i], newC = currC + dc[i];
                int newDay = currDay + 1;

                if(newR < 0 || newR >= R) continue;
                if(newC < 0 || newC >= C) continue;
                if(visit[newR][newC] == true) continue;
                if(grid[newR][newC] != 1) continue;

                q.push({{ newR, newC }, newDay});
                totalFreshOrange--;
                visit[newR][newC] = true;
            }
        }

        return totalFreshOrange > 0 ? -1 : day;
    }
};
