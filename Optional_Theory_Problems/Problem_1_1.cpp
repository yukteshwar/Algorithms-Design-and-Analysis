/* 
Algorithms: Design and Analysis, Part 1

Optional Theory Problem 1.1:

Find second largest number in an array in at most n + log(n) - 2 comparisons.

@author: Yukteshwar Baranwal
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/* Function to print the second largest elements */
void printSecondLargest(const vector<int>&);

// Efficient Algorithm with at most n + log(n) - 2 comparisons.
// Reference http://users.csc.calpoly.edu/~dekhtyar/349-Spring2010/lectures/lec03.349.pdf
// Algorithm findSecondMax() for finding the second largest element
// in an array, and function findMaxTournament() used in it.
int findSecondMax(const vector<int>&);
vector<int> findMaxTournament(int, int, const vector<int>&);

int main()
{
    vector<int> data{10,9,5,4,11,100,120,110};//{12, 35, 1, 10, 34, 1};
    //printSecondLargest(data);
    cout << findSecondMax(data) << endl;
    return 0;
}

void printSecondLargest(const vector<int> &data)
{
    /* There should be atleast two elements */
    if (data.size() < 2)
    {
        cout<< "Invalid Input" << endl;
        return;
    }
    
    int first = INT_MIN;
    int second = INT_MIN;
    
    for (auto x : data)
    {
        /* If current element is smaller than first
           then update both first and second */
        if (x > first)
        {
            second = first;
            first = x;
        }
        /* If arr[i] is in between first and 
           second then update second  */
        else if (x > second && x != first)
        second = x;
    }

    if(second == INT_MIN)
    cout << "There is no second largest element" << endl;
    else
    cout << "The second largest element is " << second << endl;    
}

int findSecondMax(const vector<int>& data)
{
    // n-1 comparisons
    vector<int> firstCompared = findMaxTournament(0, data.size()-1, data);
    //log(n)-1 comparions
    vector<int> secondCompared = findMaxTournament(2, firstCompared[0]-1, firstCompared);
    //Total n + log(n) -2 comparisons
    return secondCompared[1];
}

vector<int> findMaxTournament(int low, int high, const vector<int>& data)
{
    if(low == high)
    {
        vector<int> compared{2, data[low]};
        return compared;
    }

    vector<int> compared1 = findMaxTournament(low, (low+high)/2, data);
    vector<int> compared2 = findMaxTournament((low+high)/2 + 1, high, data);

    if(compared1[1] > compared2[1])
    {
        int k = compared1[0] + 1;
        vector<int> newCompared1(k);
        copy(compared1.begin(), compared1.begin()+compared1[0], newCompared1.begin());
        newCompared1[0] = k;
        newCompared1[k-1] = compared2[1];
        return newCompared1;
    }
    else
    {
        int k = compared2[0] + 1;
        vector<int> newCompared2(k);
        copy(compared2.begin(), compared2.begin()+compared2[0], newCompared2.begin());
        newCompared2[0] = k;
        newCompared2[k-1] = compared1[1];
        return newCompared2;
    }
}