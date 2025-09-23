#include <iostream>
#include <cmath>
using namespace std;

using ll = long long;
ll getIndex(ll totalsize, ll x, ll y) {
    return x * totalsize + y;
}

void placeL(ll matrix[], ll totalsize, ll n, ll leftCornerX, ll leftCornerY, ll missingX, ll missingY, ll &number)
{
    if (n == 2) {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                ll currX = leftCornerX + i;
                ll currY = leftCornerY + j;
                if (currX != missingX || currY != missingY)
                {
                    matrix[getIndex(totalsize, currX, currY)] = number;
                }
            }
        }
        number++;
        return;
    } // base case, directly place the L

    ll half = n / 2;            // split the board into 4 quadrants
    ll currTile = number++; // current tile number

    // determine where the missing tile is
    // top left
    if (missingX < leftCornerX + half && missingY < leftCornerY + half)
    {
        // place one L tile in the middle, spreading into other 3 quadrants
        matrix[getIndex(totalsize, leftCornerX + half - 1, leftCornerY + half)] = currTile; // top right corner
        matrix[getIndex(totalsize, leftCornerX + half, leftCornerY + half - 1)] = currTile; // bottom left corner
        matrix[getIndex(totalsize, leftCornerX + half, leftCornerY + half)] = currTile;     // bottom right corner
        // recurse on 3 more quadrants
        placeL(matrix, totalsize, half, leftCornerX, leftCornerY, missingX, missingY, number);
        placeL(matrix, totalsize, half, leftCornerX, leftCornerY + half, leftCornerX + half - 1, leftCornerY + half, number);
        placeL(matrix, totalsize, half, leftCornerX + half, leftCornerY, leftCornerX + half, leftCornerY + half - 1, number);
        placeL(matrix, totalsize, half, leftCornerX + half, leftCornerY + half, leftCornerX + half, leftCornerY + half, number);
    }
    // top right
    else if (missingX < leftCornerX + half && missingY >= leftCornerY + half)
    {
        matrix[getIndex(totalsize, leftCornerX + half - 1, leftCornerY + half - 1)] = currTile; 
        matrix[getIndex(totalsize, leftCornerX + half, leftCornerY + half - 1)] = currTile;    
        matrix[getIndex(totalsize, leftCornerX + half, leftCornerY + half)] = currTile;         
        placeL(matrix, totalsize, half, leftCornerX, leftCornerY, leftCornerX + half - 1, leftCornerY + half - 1, number);      
        placeL(matrix, totalsize, half, leftCornerX, leftCornerY + half, missingX, missingY, number);                     
        placeL(matrix, totalsize, half, leftCornerX + half, leftCornerY, leftCornerX + half, leftCornerY + half - 1, number);   
        placeL(matrix, totalsize, half, leftCornerX + half, leftCornerY + half, leftCornerX + half, leftCornerY + half, number);
    }
    // bottom left
    else if (missingX >= leftCornerX + half && missingY < leftCornerY + half)
    {
        matrix[getIndex(totalsize, leftCornerX + half - 1, leftCornerY + half - 1)] = currTile; 
        matrix[getIndex(totalsize, leftCornerX + half - 1, leftCornerY + half)] = currTile;     
        matrix[getIndex(totalsize, leftCornerX + half, leftCornerY + half)] = currTile;         
        placeL(matrix, totalsize, half, leftCornerX, leftCornerY, leftCornerX + half - 1, leftCornerY + half - 1, number);      
        placeL(matrix, totalsize, half, leftCornerX, leftCornerY + half, leftCornerX + half - 1, leftCornerY + half, number);   
        placeL(matrix, totalsize, half, leftCornerX + half, leftCornerY, missingX, missingY, number);                      
        placeL(matrix, totalsize, half, leftCornerX + half, leftCornerY + half, leftCornerX + half, leftCornerY + half, number);
    }
    // bottom right
    else
    {
        matrix[getIndex(totalsize, leftCornerX + half - 1, leftCornerY + half - 1)] = currTile;
        matrix[getIndex(totalsize, leftCornerX + half - 1, leftCornerY + half)] = currTile;
        matrix[getIndex(totalsize, leftCornerX + half, leftCornerY + half - 1)] = currTile;
        placeL(matrix, totalsize, half, leftCornerX, leftCornerY, leftCornerX + half - 1, leftCornerY + half - 1, number);
        placeL(matrix, totalsize, half, leftCornerX, leftCornerY + half, leftCornerX + half - 1, leftCornerY + half, number);
        placeL(matrix, totalsize, half, leftCornerX + half, leftCornerY, leftCornerX + half, leftCornerY + half - 1, number);
        placeL(matrix, totalsize, half, leftCornerX + half, leftCornerY + half, missingX, missingY, number);  
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
        ll number = 1;
        placeL(matrix, n, n, 0, 0, x, y, number);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << matrix[getIndex(n, i, j)] << ' ';
            }
            cout << '\n';
        }
        delete[] matrix;
    }
    return 0;
}