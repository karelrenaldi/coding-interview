#include<queue>
#include<vector>

using namespace std;

#define pii pair<int, int>

class Solution {
public:
    const int dr[4] = {-1, 0, 1, 0};
    const int dc[4] = {0, 1, 0, -1};

    int R, C, visited;
    vector<vector<bool>> isX;
    vector<vector<int>> visit;

    bool isBorder(int r, int c) {
        return (r == 0 || r == R - 1 || c == 0 || c == C - 1);
    }

    void solve(vector<vector<char>>& board) {
        visited = 1;
        R = board.size(), C = board[0].size();

        visit.assign(R, vector<int>(C, 0));
        isX.assign(R, vector<bool>(C, true));

        queue<pii> q;
        for(int r = 0; r < R; ++r)
            for(int c = 0; c < C; ++c)
                if(isBorder(r, c) && board[r][c] == 'O') {
                    q.push({ r, c });
                    isX[r][c] = false;
                    visit[r][c] = visited;
                }

        while(!q.empty()) {
            pii curr = q.front();
            q.pop();

            int currR = curr.first, currC = curr.second;
            for(int i = 0; i < 4; ++i) {
                int newR = currR + dr[i], newC = currC + dc[i];

                if(newR < 0 || newR >= R) continue;
                if(newC < 0 || newC >= C) continue;
                if(board[newR][newC] == 'X') continue;
                if(visit[newR][newC] == visited) continue;

                q.push({ newR, newC });
                isX[newR][newC] = false;
                visit[newR][newC] = visited;
            }
        }

        for(int r = 0; r < R; ++r)
            for(int c = 0; c < C; ++c)
                board[r][c] = isX[r][c] ? 'X' : 'O';
    }
};
