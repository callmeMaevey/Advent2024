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

    //parse out tokens with regex
    const regex mul_regex(R"(mul\([0-9]{1,3}\,[0-9]{1,3}\))");
    regex_token_iterator regex_iterator ( file_contents.begin(), file_contents.end(), mul_regex );
    regex_token_iterator<string::iterator> end; // default constructor = end-of-sequence:
    vector<string> tokens;
    while (regex_iterator!=end) tokens.push_back(regex_iterator++->str());

    int total = 0;
    for (auto token : tokens) {
        //string manipulation
        const size_t substring_start = token.find("(") + 1; //lop off mul(
        const unsigned long substring_length = token.size() - substring_start - 1; // lop off )
        token = token.substr( substring_start , substring_length );
        token.replace(token.find(','),1,1,' ');

        // output
        istringstream iss(token) ;
        int x, y; iss >> x >> y;
        total += x*y;
    }
    return total;
}

int part2_total(string file_contents) {

    //parse out tokens with regex
    const regex mul_regex(R"(mul\([0-9]{1,3}\,[0-9]{1,3}\)|do\(\)|don't\(\))");
    regex_token_iterator regex_iterator ( file_contents.begin(), file_contents.end(), mul_regex );
    regex_token_iterator<string::iterator> end; // default constructor = end-of-sequence:
    vector<string> tokens;
    while (regex_iterator!=end) tokens.push_back(regex_iterator++->str());

    int total = 0;
    bool mul_enabled = true;
    for (auto token : tokens) {
        if (token == "do()") { mul_enabled = true; continue; }
        if (token == "don't()") { mul_enabled = false; continue; }
        if (mul_enabled) {
            //string manipulation
            const size_t substring_start = token.find("(") + 1;
            const unsigned long substring_length = token.size() - substring_start - 1;
            token = token.substr( substring_start , substring_length );
            token.replace(token.find(','),1,1,' ');
            // output
            istringstream iss(token) ;
            int x, y; iss >> x >> y;
            total += x*y;
        }
    }
    return total;
}
int main() {
    const string fileName = "Day 3/day3.txt";
    const string fileContents = read_file(fileName);
    cout << "part 1 total: " << part1_total(fileContents) << endl;
    cout << "part 2 total: " << part2_total(fileContents) << endl;
    return 0;
}