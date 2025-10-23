#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
using ll = long long;


void placeL(vector<vector<int>> &board, int k, int x, int y, ll leftCornerX, ll leftCornerY, ll &number){
    ll size = pow(2, k);
    ll midX = (leftCornerX + size) / 2;
    ll midY = (leftCornerY + size) / 2;
    if (x < midX && y < midY){
        board[midX][midY+1] = number;
        board[midX+1][midY] = number;
        board[midX+1][midY+1] = number;
        number++;
        placeL(board, k - 1, x, y, leftCornerX, leftCornerY, number);
        placeL(board, k - 1, midX, midY+1, leftCornerX, leftCornerY + midY + 1, number);
        placeL(board, k - 1, midX + 1, midY, leftCornerX + midX + 1, leftCornerY + midY + 1, number);
        placeL(board, k - 1, midX + 1, midY + 1, leftCornerX + midX + 1, leftCornerY + midY + 1, number);
    }
}

int main(){
    int T;
    cin >> T;
    while (T--){
        int k, x, y;
        cin >> k >> x >> y;
        ll size = pow(2, k);
        vector<vector<int>> board(size, vector<int>(size, 0));
        board[x][y] = 0;
        ll number = 1;
        placeL(board, k, x - 1, y - 1, 0, 0, number);
        for(int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                cout << board[i][j] << ' ';
            }
            cout << '\n';
        }
    }
    return 0;
}