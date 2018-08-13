/* 
Algorithms: Design and Analysis, Part 1

Optional Theory Problem 2.2:

Global minimum in 2d-grid in O(n) complexity

@author: Yukteshwar Baranwal
*/

#include <iostream>
#include <valarray>
#include <random>
#include <climits>
#include <cmath>

using namespace std;

enum class GridLocType
{
    CORNER,
    SIDE,
    INNER,
    NOTEXIST
};

typedef struct
{
    GridLocType locType; // NOTEXIST if there is no local minimum
    int rLoc;            // row; -1 if there is no local minimum
    int cLoc;            // column; -1 if there is no local minimum
    int value;           // Irrelevant if there is no local minimum

} LocalMinData;

// Utility method to check whether a point is
// inside the grid or not
bool inline IsInsideGrid(size_t rLoc, size_t cLoc, size_t nRow, size_t nCol)
{
    return (rLoc >= 0 && rLoc < nRow && cLoc >= 0 && cLoc < nCol);
}

LocalMinData FindLocalMin(const valarray<int> &); //, size_t, size_t);

LocalMinData LocalMin(const valarray<int> &, size_t, size_t, size_t, size_t);

size_t GlobalMin1D(const valarray<int> &);

const size_t nRow = 7;
const size_t nCol = 5;
const size_t offset = 2;
int main()
{
    // Define 2D grid as per the given problem
    valarray<int> grid(INT_MAX, ((nRow + offset) * (nCol + offset)));

    random_device generator;
    uniform_int_distribution<int> distribution(0, 2 * nRow * nCol);

    for (int r = 1; r < (nRow + offset - 1); r++)
        for (int c = 1; c < (nCol + offset - 1); c++)
            grid[r * (nCol + offset) + c] = distribution(generator);

    for (int r = 0; r < (nRow + offset); r++)
    {
        for (int c = 0; c < (nCol + offset); c++)
            cout << grid[r * (nCol + offset) + c] << '\t';
        cout << endl;
    }

    LocalMinData localMinData = FindLocalMin(grid); //, nRow + offset, nCol + offset);

    return 0;
}

LocalMinData FindLocalMin(const valarray<int> &grid) //, size_t nRow, size_t nCol)
{
    return LocalMin(grid, 0, nRow + 1, 0, nCol + 1);
}

LocalMinData LocalMin(const valarray<int> &grid, size_t rowUp, size_t rowDown, size_t colLeft, size_t colRight)
{
    LocalMinData localMinData;

    //http://courses.csail.mit.edu/6.006/spring11/lectures/lec02.pdf

    //https://stackoverflow.com/questions/15778377/get-the-first-column-of-a-matrix-represented-by-a-vector-of-vectors/15799557#15799557
    //https://stackoverflow.com/questions/23949642/c-2d-vector-search-by-column

    //Global minimum in boundary, center row, center column
    valarray<size_t> minIndices(6);
    valarray<int> minValues(6);
    //First row
    size_t startFirstRow = rowUp * (nCol + offset) + colLeft;
    size_t sizeFirstRow = colRight - colLeft + 1;
    size_t strideFirstRow = 1;
    slice sliceFirstRow = slice(startFirstRow, sizeFirstRow, strideFirstRow);
    valarray<int> firstRow = grid[sliceFirstRow];
    minIndices[0] = GlobalMin1D(firstRow);
    minValues[0] = firstRow[minIndices[0]];

    // cout << "First Row" << endl;
    // for (size_t i = 0; i < colRight - colLeft + 1; i++)
    //     cout << firstRow[i] << '\t';
    // cout << endl;

    //Center row
    size_t startCenterRow = floor((rowDown - rowUp) / 2) * (nCol + offset) + colLeft;
    size_t sizeCenterRow = colRight - colLeft + 1;
    size_t strideCenterRow = 1;
    slice sliceCenterRow = slice(startCenterRow, sizeCenterRow, strideCenterRow);
    valarray<int> centerRow = grid[sliceCenterRow];
    minIndices[1] = GlobalMin1D(centerRow);
    minValues[1] = centerRow[minIndices[1]];

    // cout << "Center row" << endl;
    // for (size_t i = 0; i < colRight - colLeft + 1; i++)
    //     cout << centerRow[i] << '\t';
    // cout << endl;

    //Last row
    size_t startLastRow = rowDown * (nCol + offset) + colLeft;
    size_t sizeLastRow = colRight - colLeft + 1;
    size_t strideLastRow = 1;
    slice sliceLastRow = slice(startLastRow, sizeLastRow, strideLastRow);
    valarray<int> lastRow = grid[sliceLastRow];
    minIndices[2] = GlobalMin1D(lastRow);
    minValues[2] = lastRow[minIndices[2]];

    // cout << "Last row" << endl;
    // for (size_t i = 0; i < colRight - colLeft + 1; i++)
    //     cout << lastRow[i] << '\t';
    // cout << endl;

    //First col
    size_t startFirstCol = rowUp * (nCol + offset) + colLeft;
    size_t sizeFirstCol = rowDown - rowUp + 1;
    size_t strideFirstCol = colRight - colLeft + 1;
    slice sliceFirstCol = slice(startFirstCol, sizeFirstCol, strideFirstCol);
    valarray<int> firstCol = grid[sliceFirstCol];
    minIndices[3] = GlobalMin1D(firstCol);
    minValues[3] = firstCol[minIndices[3]];

    // cout << "First col" << endl;
    // for (size_t i = 0; i < rowDown - rowUp + 1; i++)
    //     cout << firstCol[i] << '\t';
    // cout << endl;

    //Center col
    size_t startCenterCol = rowUp * (nCol + offset) + floor((colRight - colLeft) / 2);
    size_t sizeCenterCol = rowDown - rowUp + 1;
    size_t strideCenterCol = colRight - colLeft + 1;
    slice sliceCenterCol = slice(startCenterCol, sizeCenterCol, strideCenterCol);
    valarray<int> centerCol = grid[sliceCenterCol];
    minIndices[4] = GlobalMin1D(centerCol);
    minValues[4] = centerCol[minIndices[4]];

    // cout << "Center col" << endl;
    // for (size_t i = 0; i < rowDown - rowUp + 1; i++)
    //     cout << centerCol[i] << '\t';
    // cout << endl;

    //Last col
    size_t startLastCol = rowUp * (nCol + offset) + colRight;
    size_t sizeLastCol = rowDown - rowUp + 1;
    size_t strideLastCol = colRight - colLeft + 1;
    slice sliceLastCol = slice(startLastCol, sizeLastCol, strideLastCol);
    valarray<int> lastCol = grid[sliceLastCol];
    minIndices[5] = GlobalMin1D(lastCol);
    minValues[5] = lastCol[minIndices[5]];

    // cout << "Last col" << endl;
    // for (size_t i = 0; i < rowDown - rowUp + 1; i++)
    //     cout << lastCol[i] << '\t';
    // cout << endl;

    // cout << "min Indices" << endl;
    // for (size_t i = 0; i < 6; i++)
    //     cout << minIndices[i] << '\t';
    // cout << endl;

    // cout << "min Values" << endl;
    // for (size_t i = 0; i < 6; i++)
    //     cout << minValues[i] << '\t';
    // cout << endl;

    return localMinData;
}

size_t GlobalMin1D(const valarray<int> &array1D)
{
    size_t arraySize = array1D.size();
    size_t m = 0;
    for (size_t i = 0; i < arraySize; i++)
    {
        if (array1D[i] < array1D[m])
            m = i;
    }
    return m;
}