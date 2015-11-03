#include <iostream>
#include <stdlib.h> 
#include <vector>

using namespace std;

vector<int> resSampling(vector<int> &stream, int k) {
    vector<int> sample(k);
    int n = stream.size();
    for (int i = 0; i < k; i++) {
        sample[i] = stream[i];
    }
    for (int i = k; i < n; i++) {
        int j = rand() % (i+1);
        if (j < k) {
            sample[j] = stream[i];
        }
    }
    return sample;
}

int main() {
	vector<int> stream = {1,2,3,4,5,6,7,8,9,10};
	vector<int> sample = resSampling(stream, 5);
	for (int i = 0; i < sample.size(); i++) {
	    cout << sample[i] << " ";
	}
	cout << endl;
	return 0;
}
