#include <iostream>
#include <cmath>
using namespace std;
int number = 1;

using ll = long long;
ll getIndex(ll n, ll x, ll y) {
    return x * n + y;
}

void placeL(ll matrix[], ll n, ll leftCornerX, ll leftCornerY, ll missingX, ll missingY)
{
    if (n == 1)
        return; // base case

    ll half = n / 2;            // split the board into 4 quadrants
    ll currTile = number++; // current tile number

    // determine where the missing tile is
    // top left
    if (missingX < leftCornerX + half && missingY < leftCornerY + half)
    {
        // place one L tile in the middle, spreading into other 3 quadrants
        matrix[getIndex(n, leftCornerX + half - 1, leftCornerY + half)] = currTile; // top right corner
        matrix[getIndex(n, leftCornerX + half, leftCornerY + half - 1)] = currTile; // bottom left corner
        matrix[getIndex(n, leftCornerX + half, leftCornerY + half)] = currTile;     // bottom right corner

        // recurse on 3 more quadrants
        placeL(matrix, half, leftCornerX, leftCornerY, missingX, missingY);
        placeL(matrix, half, leftCornerX, leftCornerY + half, leftCornerX + half - 1, leftCornerY + half);
        placeL(matrix, half, leftCornerX + half, leftCornerY, leftCornerX + half, leftCornerY + half - 1);
        placeL(matrix, half, leftCornerX + half, leftCornerY + half, leftCornerX + half, leftCornerY + half);
    }
    // top right
    else if (missingX < leftCornerX + half && missingY >= leftCornerY + half)
    {
        matrix[getIndex(n, leftCornerX + half - 1, leftCornerY + half - 1)] = currTile; 
        matrix[getIndex(n, leftCornerX + half, leftCornerY + half - 1)] = currTile;    
        matrix[getIndex(n, leftCornerX + half, leftCornerY + half)] = currTile;         

        placeL(matrix, half, leftCornerX, leftCornerY, leftCornerX + half - 1, leftCornerY + half - 1);      
        placeL(matrix, half, leftCornerX, leftCornerY + half, missingX, missingY);                     
        placeL(matrix, half, leftCornerX + half, leftCornerY, leftCornerX + half, leftCornerY + half - 1);   
        placeL(matrix, half, leftCornerX + half, leftCornerY + half, leftCornerX + half, leftCornerY + half);
    }
    // bottom left
    else if (missingX >= leftCornerX + half && missingY < leftCornerY + half)
    {
        matrix[getIndex(n, leftCornerX + half - 1, leftCornerY + half - 1)] = currTile; 
        matrix[getIndex(n, leftCornerX + half - 1, leftCornerY + half)] = currTile;     
        matrix[getIndex(n, leftCornerX + half, leftCornerY + half)] = currTile;         

        placeL(matrix, half, leftCornerX, leftCornerY, leftCornerX + half - 1, leftCornerY + half - 1);      
        placeL(matrix, half, leftCornerX, leftCornerY + half, leftCornerX + half - 1, leftCornerY + half);   
        placeL(matrix, half, leftCornerX + half, leftCornerY, missingX, missingY);                      
        placeL(matrix, half, leftCornerX + half, leftCornerY + half, leftCornerX + half, leftCornerY + half);
    }
    // bottom right
    else
    {
        matrix[getIndex(n, leftCornerX + half - 1, leftCornerY + half - 1)] = currTile;
        matrix[getIndex(n, leftCornerX + half - 1, leftCornerY + half)] = currTile;
        matrix[getIndex(n, leftCornerX + half, leftCornerY + half - 1)] = currTile;

        placeL(matrix, half, leftCornerX, leftCornerY, leftCornerX + half - 1, leftCornerY + half - 1);
        placeL(matrix, half, leftCornerX, leftCornerY + half, leftCornerX + half - 1, leftCornerY + half);
        placeL(matrix, half, leftCornerX + half, leftCornerY, leftCornerX + half, leftCornerY + half - 1);
        placeL(matrix, half, leftCornerX + half, leftCornerY + half, missingX, missingY);  
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--){
        int k, x, y;
        cin >> k >> x >> y;
        ll n = 1LL << k;
        x--;
        y--;
        ll *matrix = new ll[n * n]();
        matrix[getIndex(n, x, y)] = 0;
        number = 1;
        placeL(matrix, n, 0, 0, x, y);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << matrix[getIndex(n, i, j)] << ' ';
            }
            cout << '\n';
        }
    }
    return 0;
}