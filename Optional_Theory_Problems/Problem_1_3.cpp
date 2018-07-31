/* 
Algorithms: Design and Analysis, Part 1

Optional Theory Problem 1.1:

Find index i in a sorted array such that a[i] = 1 in fastest algorithm.

@author: Yukteshwar Baranwal
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
// Return index i such that a[i] = i
// Return -1 if not found
// Complexity O(log n)
int findIdx(const vector<int> &);

int main()
{
    vector<int> data{-1, 0, 2, 5, 6, 7, 9};
    int idx = findIdx(data);
    cout << idx << endl;

    data = vector<int>{-2, -1, 1, 2, 5, 7, 9};
    idx = findIdx(data);
    cout << idx << endl;

    data = vector<int>{-23, -1, 0, 1, 2, 4, 6};
    idx = findIdx(data);
    cout << idx << endl;
    return 0;
}

int findIdx(const vector<int> &data)
{
    int low = 0;
    int high = data.size() - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;

        if ((data[mid] - mid) > 0)
            high = mid - 1;
        else if ((data[mid] - mid) < 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}
