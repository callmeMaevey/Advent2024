//
// Created by Maeve Kennedy on 12/3/24.
//
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include <iterator>
#include <iostream>


using namespace std;
string read_file( const string& fileName) {
    ifstream file(fileName);
    if (!(file.is_open())) { throw runtime_error("Could not open file " + fileName); }

    string  result ;
    string line;
    while (getline(file, line)) { result += line + "\n"; }
    return result;
}
int part1_total(string file_contents) {
    // default constructor = end-of-sequence:
    std::regex_token_iterator<std::string::iterator> end;

    std::regex mul_regex(R"(mul\([0-9]{1,3}\,[0-9]{1,3}\))");
    std::regex_token_iterator<std::string::iterator> a ( file_contents.begin(), file_contents.end(), mul_regex );
    vector<string> tokens;
    while (a!=end) { tokens.push_back(a++->str()); }
    int total = 0;
    for (auto token : tokens) {
        token.erase(token.begin(), token.begin()+4);
        token.erase(token.end()-1, token.end());
        token.replace(token.find(','),1,1,' ');
        istringstream iss(token);
        int x, y; iss >> x >> y;
        total += x*y;
    }
    return total;
}

int part2_total(string file_contents) {
    // default constructor = end-of-sequence:
    std::regex_token_iterator<std::string::iterator> end;

    std::regex mul_regex(R"(mul\([0-9]{1,3}\,[0-9]{1,3}\)|do\(\)|don't\(\))");
    std::regex_token_iterator<std::string::iterator> a ( file_contents.begin(), file_contents.end(), mul_regex );
    vector<string> tokens;
    while (a!=end) { tokens.push_back(a++->str()); }
    int total = 0;
    bool mul_enabled = true;
    for (auto token : tokens) {
        if (token == "do()") {  mul_enabled = true; continue;}
        if (token == "don't()") {  mul_enabled = false; continue;}
        if (mul_enabled) {
            token.erase(token.begin(), token.begin()+4);
            token.erase(token.end()-1, token.end());
            token.replace(token.find(','),1,1,' ');
            istringstream iss(token);
            int x, y; iss >> x >> y;
            total += x*y;
        }
    }
    return total;
}
int main() {
    const string fileName = "Day 3/day3.txt";

    const std::string str = read_file(fileName);
    cout << "total: " << part1_total(str) << endl;
    cout << "total part2: " << part2_total(str) << endl;
    return 0;

}