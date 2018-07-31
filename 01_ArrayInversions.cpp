/* 
Algorithms: Design and Analysis, Part 1

Programming assignment 1:

count the number of inversions in the given list in O(n*log(n)).

@author: Yukteshwar Baranwal
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

long int CountInversions(vector<int>);
long int SortAndCountInversions(vector<int>, size_t, size_t);
long int MergeAndCountSplitInversions(vector<int>, size_t, size_t, size_t);

int main()
{
    vector<int> data1{1, 2, 3, 4, 5, 6};
    cout << CountInversions(data1) << endl;
    vector<int> data2{6, 5, 4, 3, 2, 1};
    cout << CountInversions(data2) << endl;
    vector<int> data3{1, 3, 5, 2, 4, 6};
    cout << CountInversions(data3) << endl;

    vector<int> dataFromFile;
    ifstream dataFile;
    dataFile.open("./Data_Files/IntegerArray.txt", ifstream::in);
    if (!dataFile.is_open())
        cout << "Unable to open file" << endl;

    string line;

    while (getline(dataFile, line))
        dataFromFile.push_back(stoi(line));

    cout << dataFromFile.size() << endl;
    cout << CountInversions(dataFromFile) << endl;

    return 0;
}

long int CountInversions(vector<int> dataArray)
{
    return SortAndCountInversions(dataArray, 0, dataArray.size() - 1);
}

long int SortAndCountInversions(vector<int> dataArray, size_t start, size_t end)
{
    if (start == end)
        return 0;
    else
    {
        long int x = SortAndCountInversions(dataArray, start, floor((start + end) / 2));
        long int y = SortAndCountInversions(dataArray, floor((start + end) / 2) + 1, end);
        long int z = MergeAndCountSplitInversions(dataArray, start, floor((start + end) / 2) + 1, end);
        return x + y + z;
    }
}

long int MergeAndCountSplitInversions(vector<int> dataArray, size_t start, size_t mid, size_t end)
{
    size_t i = start;
    size_t j = mid;
    vector<int> res;
    long int inv = 0;

    while (i < mid || j <= end)
    {
        if (i == mid)
        {
            res.push_back(dataArray[j]);
            j++;
        }
        else if (j > end)
        {
            res.push_back(dataArray[i]);
            i++;
        }
        else if (dataArray[i] <= dataArray[j])
        {
            res.push_back(dataArray[i]);
            i++;
        }
        else
        {
            inv += (mid - i); // Split inversion detected
            res.push_back(dataArray[j]);
            j++;
        }
    }
    i = start;
    while (i <= end)
    {
        dataArray[i] = res[i - start];
        i++;
    }
    return inv;
}
