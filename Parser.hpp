#ifndef PARSER_HPP
#define PARSER_HPP
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <sstream>

using namespace std;

class Parser {
    private:
        vector<string> tokens;
        int inputIndex;
        string result;
        map<string, int> symbolTable; // Simple symbol table to store variable values
    public:
        Parser(const vector<string>& tokens) : tokens(tokens), inputIndex(0), result(""){}
        bool validateInput();
        void evaluateExpression();
        string returnResult() const;
};

#endif // PARSER_HPP