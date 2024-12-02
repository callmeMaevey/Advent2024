#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>


using namespace std;

int main() {
    vector<int> listA;
    vector<int> listB;

    ifstream infile("Day 1/day1.txt");

    string line;
    int a, b;
    while (infile >> a >> b) {
        listA.push_back(a);
        listB.push_back(b);
    }

    sort(listA.begin(), listA.end());
    sort(listB.begin(), listB.end());
    int distance = 0;
    int similarity = 0;
    for (int i = 0; i < listA.size(); i++) {
        distance += abs(listA[i]-listB[i]);
        similarity += listA[i] * count(listB.begin(), listB.end(), listA[i] );
    }
    cout << "distance: " << distance << endl;
    cout << "similarity: " << similarity << endl;
    return 0;
}

