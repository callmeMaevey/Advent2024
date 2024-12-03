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
    while (getline(file, line)) {
        result += line + "\n";
    }
    return result;
}

int main() {
    const string fileName = "Day 3/day3.txt";

    std::regex mul_regex(R"(mul\([0-9]{1,3}\,[0-9]{1,3}\))");
    std::string str = read_file(fileName);

    // default constructor = end-of-sequence:
    std::regex_token_iterator<std::string::iterator> end;

    std::regex_token_iterator<std::string::iterator> a ( str.begin(), str.end(), mul_regex );
    vector<string> tokens;
    while (a!=end) {
        tokens.push_back(a++->str());
    }
    int total = 0;
    for (auto token : tokens) {
        token.erase(token.begin(), token.begin()+4);
        token.erase(token.end()-1, token.end());
        token.replace(token.find(','),1,1,' ');
        istringstream iss(token);
        int x, y; iss >> x >> y;
        total += x*y;

    }
    cout << "total: " << total << endl;
    return 0;

}