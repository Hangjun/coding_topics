Given n arrays, find the kth smallest element among them. 

Kth Smallest Element in n Sorted Arrays: Single Machine, k Small:

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

class Element {
public:
    Element(int _value, int _arrayID, int _index) {
        value = _value;
        arrayID = _arrayID;
        index = _index;
    }
    
    bool operator < (const Element &e) const {
        return value > e.value; // min heap
    }
    
    int value;
    int arrayID;
    int index;
};


int kthSmallestInNArrays(vector<vector<int>> matrix, int k) {
    // we assume k is smaller than the total number in the matrix
    if (matrix.empty() || k <= 0)  return INT_MAX;
    int n = matrix.size();
    // preprocess: sort each array
    for (int i = 0; i < n; i++) {
        sort(matrix[i].begin(), matrix[i].end());
    }
    // min heap to keep track of the smallest element
    priority_queue<Element> minHeap;
    // initialize minHeap
    for (int i = 0; i < n; i++) {
        minHeap.push(Element(matrix[i][0], i, 0));
    }
    // counter to keep track of the number of smallest poped
    for (int counter = 0; counter < k-1; counter++) {
        Element curSmallest = minHeap.top();
        minHeap.pop();
        int arrayID = curSmallest.arrayID;
        int index = curSmallest.index;
        if (index < matrix[arrayID].size()-1) {
            minHeap.push(Element(matrix[arrayID][index+1], arrayID, index+1));
        }// else matrix[arrayID] is fully traversed: ignore it
    }
    return (minHeap.top()).value;
}

int main() {
	vector<vector<int>> matrix = {{2,3,4,5}, {0}};
	cout << "kth smallest element = " << kthSmallestInNArrays(matrix, 5);
	return 0;
}

