#include <iostream>
#include <array>
#include <vector>
#include <random>

using namespace std;

typedef vector<vector<int>> arrayOfInt2D;

typedef struct LocalMinData;

enum class GridLocType;
// enum class GridLocType
// {
//     CORNER,
//     SIDE,
//     INNER,
//     NOTEXIST
// };

// typedef struct 
// {
//     GridLocType locType;
//     int rLoc;
//     int cLoc;
//     int value;

// } LocalMinData;

// Utility for preallocated 2D vector
// Returns a 2D vector of dim [n, m] initialized with val (default 0)
arrayOfInt2D getArrayOfInt2D(int n, int m, int val = 0);

// Utility method to check whether a point is
// inside the grid or not
bool inline IsInsideGrid(int, int, int, int);

LocalMinData findLocalMin(const arrayOfInt2D& grid)
{

}

int main()
{
    int nCol = 9;
    int nRow = 9;

    // Define energy data of cartesian grid as per the given problem
    arrayOfInt2D grid = getArrayOfInt2D(nRow, nCol);

    random_device generator;
    uniform_int_distribution<int> distribution(-nRow * nCol, nRow * nCol);

    for (int r = 0; r < nRow; r++)
        for (int c = 0; c < nCol; c++)
            grid[r][c] = distribution(generator);

    for (auto row : grid)
    {
        for (auto value : row)
            cout << value << '\t';
        cout << endl;
    }

    return 0;
}

enum class GridLocType
{
    CORNER,
    SIDE,
    INNER,
    NOTEXIST
};

typedef struct 
{
    GridLocType locType; //NOTEXIST if there is no local minimum 
    int rLoc; // -1 if there is no local minimum
    int cLoc; //-1 if there is no local minimum
    int value; // Irrelevant if there is no local minimum

} LocalMinData;

arrayOfInt2D getArrayOfInt2D(int n, int m, int val)
{
    arrayOfInt2D arrayInt2D(n, vector<int>(m, val));
    return arrayInt2D;
}

bool inline IsInsideGrid(int rLoc, int cLoc, int nRow, int nCol)
{
    return (rLoc >= 0 && rLoc < nRow && cLoc >= 0 && cLoc < nCol);
}

LocalMinData findLocalMin(const arrayOfInt2D& grid)
{
    LocalMinData localMinData;

    return localMinData;
}
