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
int comparisons = 0;
enum class Pivot
{
    FIRST,
    LAST,
    MEDIAN
};

void quicksort(vector<int>&, Pivot);
void quicksort(vector<int>&, int, int, Pivot);
void swap(vector<int>&, int, int);
bool isMedian(vector<int>&, int, int, int);

int main()
{
    //vector<int> testdata{1,2,3,4,5,6,7,8};
    //vector<int> testdata{8,7,6,5,4,3,2,1};
    vector<int> testdata{3,8,2,5,1,4,7,6};
    comparisons = 0;
    quicksort(testdata, Pivot::FIRST);
    cout << comparisons << endl;

    comparisons = 0;
    quicksort(testdata, Pivot::LAST);
    cout << comparisons << endl;

    comparisons = 0;
    quicksort(testdata, Pivot::MEDIAN);
    cout << comparisons << endl;

    vector<int> dataFromFile;
    ifstream dataFile;
    dataFile.open("QuickSort.txt", ifstream::in);
    if (!dataFile.is_open())
        cout << "Unable to open file" << endl;

    string line;

    while (getline(dataFile, line))
        dataFromFile.push_back(stoi(line));

    cout << dataFromFile.size() << endl;

    // Task 1
    comparisons = 0;
    vector<int> task1data = dataFromFile;
    quicksort(task1data, Pivot::FIRST);
    cout << comparisons << endl;

    // Task 2
    comparisons = 0;
    vector<int> task2data = dataFromFile;
    quicksort(task2data, Pivot::LAST);
    cout << comparisons << endl;

    // Task 1
    comparisons = 0;
    vector<int> task3data = dataFromFile;
    quicksort(task3data, Pivot::MEDIAN);
    cout << comparisons << endl;
}

void quicksort(vector<int>& data, Pivot pivot)
{
    //Sorts the array in place using the given pivot picking strategy
    //Expected running time is O(n*log(n)).
    quicksort(data, 0, data.size() - 1, pivot);
}

void quicksort(vector<int>& data, int left, int right, Pivot pivot)
{
    //Base case
    if (left >= right)
        return;

    //Picking the pivot element
    int p = 0;
    if (pivot == Pivot::FIRST)
        p = data[left];
    else if (pivot == Pivot::LAST)
    {
        p = data[right];
        swap(data, left, right);
    }

    else if (pivot == Pivot::MEDIAN)
    {
        int mid = left + ((right - left) >> 1);
        if (isMedian(data, left, mid, right))
            p = data[left];
        else if (isMedian(data, mid, left, right))
        {
            p = data[mid];
            swap(data, left, mid);
        }
        else
        {
            p = data[right];
            swap(data, left, right);
        }
    }

    //Updating the comparisons counter
    comparisons += (right - left);

    //Partitions
    int i = left + 1;
    for(int j = left + 1; j <= right; j++)
    {
        if(data[j] < p)
        {
            swap(data, i, j);
            i++;
        }
    }
    swap(data, left, i - 1);

    //Recursive calls
    quicksort(data, left, i - 2, pivot);
    quicksort(data, i, right, pivot);    
}

void swap(vector<int>& data, int i, int j)
{
    int temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

bool isMedian(vector<int>& data, int i, int j, int k)
{
  //Determines whether data[i] is a median
  bool flag1 = data[i] < data[j];
  bool flag2 = data[i] > data[k];
  bool flag3 = data[i] > data[j];
  bool flag4 = data[i] < data[k];
  return (flag1 && flag2) || (flag3 && flag4);
}