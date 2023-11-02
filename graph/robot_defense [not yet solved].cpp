#include <vector>

using namespace std;

const int MAX_N = 20;
const int OFFSET = 5;

const int dr[4] = { 0, 0, -1, 1 };
const int dc[4] = { -1, 1, 0, 0 };

int n;
int grid[MAX_N][MAX_N];
vector<int[3]> diff[10][10][10][10];

void init(int N, int mMap[MAX_N][MAX_N]) {
    n = N;

    for(int i = 0; i < 10; ++i)
        for(int j = 0; j < 10; ++j)
            for(int k = 0; k < 10; ++k)
                for(int l = 0; l < 10; ++l)
                    diff[i][j][k][l].clear();

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            grid[i][j] = mMap[i][j];

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            for(int k = 0; k < 4; ++k) {
                int keys[4] = { -5, -5, -5, -5 };

                int prev = grid[i][j];
                for(int l = 1; l < 5; l++) {
                    int ni = i + l * dr[k];
                    int nj = j + l * dc[k];

                    if(ni < 0 || nj >= n) break;
                    if(ni < 0 || nj >= n) break;

                    keys[l - 1] = grid[ni][nj] - prev;
                    prev = grid[ni][nj];

                    int key0 = keys[0] + OFFSET;
                    int key1 = keys[1] + OFFSET;
                    int key2 = keys[2] + OFFSET;
                    int key3 = keys[3] + OFFSET;
                    diff[key0][key1][key2][key3].push_back({ i, j, k });
                }
            }
        }
    }
}

int numOfPossible(int M, int mStructure[]) {
    int total = 0;

    for(int i = 0; i < 4; ++i) {

    }

    int keys[4] = { -5, -5, -5, -5 };


    return 0;
}
