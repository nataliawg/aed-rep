//
// Created by NATALIA WATSON on 18/09/2024.
//

#include <vector>
#include <set>
using namespace std;

class Solution{

public:
    bool isValidSudoku(vector<vector<char>>& board) {

        vector<set<char>> rows(9);
        vector<set<char>> cols(9);
        vector<set<char>> subgrids(9);

        for (int i = 0; i < 9; ++i){
            for (int j = 0; j < 9; ++j){
                char current = board[i][j];

                if (current == '.'){
                    continue;
                }

                int subgridIndex = (i/3) * 3 + (j/3);


                if (rows[i].count(current) || cols[j].count(current) || subgrids[subgridIndex].count(current)) {
                    return false;  
                }

                rows[i].insert(current);
                cols[j].insert(current);
                subgrids[subgridIndex].insert(current);
            }
        }

        return true;
    }
};