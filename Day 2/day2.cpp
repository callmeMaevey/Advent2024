//
// Created by Maeve Kennedy on 12/2/24.
//
#include <optional>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
vector< vector<int> > read_file( const string& fileName) {
    vector< vector<int> > result ;
    ifstream file(fileName);
    if (!(file.is_open())) { throw runtime_error("Could not open file " + fileName); }

    string line;
    while (getline(file, line)) {
        vector<int> row;
        istringstream iss(line);
        int value;
        while (iss >> value) {
            row.push_back(value);
        }
        result.push_back(row);
    }
    return result;
}

bool is_safe(const vector<int>& readings) {
    if (readings.empty()) { throw std::invalid_argument("readings vector is empty"); }
    if (readings.size() == 1) { return true; }

    optional<bool> vector_increasing;
    for (int i = 0; i < readings.size()-1; i++) {
        bool adjacent_increasing;
        const int first = readings[i];
        const int second = readings[i+1];

        // checks adjacent against global increasing/decreasing, set by the first pair
        // early returns false if the vector is not strictly increasing or decreasing
        if (first != second) { adjacent_increasing = first < second; }
        else { return false; }

        if (vector_increasing == nullopt){ vector_increasing = adjacent_increasing; }
        else if (vector_increasing != adjacent_increasing) { return false; }

        // checks to make sure the differences are in range
        const int abs_diff = abs(second - first);
        if (abs_diff < 1 || abs_diff > 3) { return false; }
    }

    return true;
}

int main() {
    const vector< vector<int> > matrix = read_file("Day 2/day2.txt");
    int total_safes = 0;
    for (auto row : matrix) {
        if (is_safe(row)) { total_safes++; }
    }
    cout << total_safes << endl;
    return 0;
}