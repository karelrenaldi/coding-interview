#include<vector>
#include<iostream>

#define matrix std::vector<std::vector<int>>
#define nl std::

class Solution {
public:
    void printMatrix(matrix& m) {
        std::cout << std::endl;
        for(auto const& r: m) {
            for(auto const& c: r) {
                std::cout << "  " << c;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    int largestMagicSquare(matrix& grid) {
        /* 
            diag1 => top left to bottom right.
            diag2 => top right to bottom left.
        */

        int R = grid.size(), C = grid[0].size(), k = std::min(R, C);
        matrix pSumRow(grid), pSumCol(grid), pSumDiag1(grid), pSumDiag2(grid);

        // Calculate prefix sum row
        for(int r = 0; r < R; ++r)
            for(int c = 1; c < C; ++c)
                pSumRow[r][c] += pSumRow[r][c - 1];
        
        // Calculate prefix sum column
        for(int c = 0; c < C; ++c)
            for(int r = 1; r < R; ++r)
                pSumCol[r][c] += pSumCol[r - 1][c];
        
        // Calculate prefix sum diagonal 1
        for(int r = 1; r < R; ++r)
            for(int c = 1; c < C; ++c)
                pSumDiag1[r][c] += pSumDiag1[r - 1][c - 1];
        
        printMatrix(pSumDiag1);

        // Calculate prefix sum diagonal 2
        for(int r = 1; r < R; ++r)
            for(int c = C - 2; c >= 0; --c)
                pSumDiag2[r][c] += pSumDiag2[r - 1][c + 1];
        
        printMatrix(pSumDiag2);
        
        return k;
    }
};

int main() {
    matrix grid = {{5, 1, 3, 1}, {9, 3, 3, 1}, {1, 3, 3, 8}};
    Solution().largestMagicSquare(grid);
}