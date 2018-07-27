/* 
Algorithms: Design and Analysis, Part 1

Optional Theory Problem 1.1:

You are a given a unimodal array of n distinct elements, 
meaning that its entries are in increasing order up until 
its maximum element, after which its elements are in 
decreasing order. Give an algorithm to compute the maximum 
element that runs in O(log n) time

@author: Yukteshwar Baranwal
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;
//Reference: https://web.stanford.edu/class/archive/cs/cs161/cs161.1138/lectures/06/Small06.pdf
int findMaxUnimodal(const vector<int> &, int, int);
int findMaxWeakUnimodal(const vector<int> &, int, int);
int max(int, int);

int main()
{
    vector<int> data{1, 3, 5, 9, 10, 15, 12, 8, 6, 4, 2, 0};
    cout << findMaxUnimodal(data, 0, data.size()) << endl;
    data = vector<int>{8, 10, 20, 80, 100, 200, 400, 500, 3, 2, 1};
    cout << findMaxUnimodal(data, 0, data.size()) << endl;
    data = vector<int>{1, 3, 50, 10, 9, 7, 6};
    cout << findMaxUnimodal(data, 0, data.size()) << endl;
    // Corner case (No decreasing part)
    data = vector<int>{10, 20, 30, 40, 50};
    cout << findMaxUnimodal(data, 0, data.size()) << endl;
    // Corner case (No increasing part)
    data = vector<int>{120, 100, 80, 20, 0};
    cout << findMaxUnimodal(data, 0, data.size()) << endl;
    // Weak Unimodal case
    data = vector<int>{1,3,4,5,7,8,10,10,13,14,10,9,6,2};
    cout << findMaxUnimodal(data, 0, data.size()) << endl;
    cout << findMaxWeakUnimodal(data, 0, data.size()) << endl;
    // Weak Unimodal case: Lower bound 
    data = vector<int>{1,1,1,1,3,1,1,1,1};
    cout << findMaxUnimodal(data, 0, data.size()) << endl;
    cout << findMaxWeakUnimodal(data, 0, data.size()) << endl;
    data = vector<int>{1,1,1,1,1,1,1,1,1};
    cout << findMaxUnimodal(data, 0, data.size()) << endl;
    cout << findMaxWeakUnimodal(data, 0, data.size()) << endl;
    return 0;
}

int findMaxUnimodal(const vector<int> &data, int low, int high)
{
    if (low == high)
        return data[low];

    int mid = (low + high) / 2;
    if (data[mid] < data[mid + 1])
        return findMaxUnimodal(data, mid + 1, high);
    else
        return findMaxUnimodal(data, low, mid);
}

int findMaxWeakUnimodal(const vector<int> &data, int low, int high)
{
    if (low == high)
        return data[low];

    int mid = (low + high) / 2;
    if (data[mid] < data[mid + 1])
        return findMaxUnimodal(data, mid + 1, high);
    else if (data[mid] > data[mid + 1])
        return findMaxUnimodal(data, low, mid);
    else
        return max(findMaxUnimodal(data, low, mid), findMaxUnimodal(data, mid + 1, high));
}

int max(int a, int b)
{
    return a > b ? a : b;
}