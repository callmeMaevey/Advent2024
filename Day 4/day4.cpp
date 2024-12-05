//
// Created by Maeve Kennedy on 12/4/24.
//
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
using namespace std;

vector< string > read_file( const string& fileName) {
    ifstream file(fileName);
    if (!(file.is_open())) { throw runtime_error("Could not open file " + fileName); }
    vector<string> result ;
    string line;
    while (getline(file, line)) result.push_back(line);
    return result;
}

void add_horizonals( vector<string>& lines, const vector<string>& file_lines) {
    for (const string& line: file_lines) lines.push_back(line);
}
void add_verticals( vector<string>& lines, const vector<string>& file_lines) {
  for (int i=0; i < file_lines[0].size(); i++) {
     string vertical;
     for (string line: file_lines){
         vertical += line[i];
     }
     lines.push_back(vertical);
  }
}
void add_diagonals_descending( vector<string>& lines, const vector<string>& file_lines) {
    int line_length = file_lines[0].size();
    int start_index = 0;
    while (start_index < line_length) {
        string diagonal_descending;
        int current_index = start_index;
        int current_line = 0;
        while ( current_index >= 0 && current_line < file_lines.size() )
            diagonal_descending += file_lines[current_line++][current_index--];
        lines.push_back(diagonal_descending);
        start_index++;
    }
}
void add_diagonals_ascending( vector<string>& lines, const vector<string>& file_lines) {
    int line_length = file_lines[0].size();
    int start_index = line_length - 1;
    while (start_index >= 0) {
        string diagonal_ascending;
        int current_index = start_index;
        int current_line = 0;
        while ( current_index < line_length && current_line < file_lines.size() )
            diagonal_ascending += file_lines[current_line++][current_index++];
        lines.push_back(diagonal_ascending);
        start_index--;
    }
}

int count_occurrences( vector<string>& lines) {
    int total = 0;
    for (string line: lines) {
        const regex xmas_regex(R"(XMAS|SAMX)");
        regex_token_iterator regex_iterator ( line.begin(), line.end(), xmas_regex );
        regex_token_iterator<string::iterator> end; // default constructor = end-of-sequence:
        while (regex_iterator!=end) {
            ++regex_iterator;
            total++;
        }
    }
    return total;
}


int main() {
    const vector<string> contents = read_file("Day 4/day4.txt");
    vector<string> all_lines;
    add_horizonals(all_lines, contents);
    add_verticals(all_lines, contents);
    add_diagonals_descending(all_lines, contents);
    add_diagonals_ascending(all_lines, contents);
    cout << "counting occurrences" << endl;
    cout << count_occurrences(all_lines) << endl;
    return 0;
}