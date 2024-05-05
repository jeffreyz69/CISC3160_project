#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Tokenizer.hpp"
#include "Parser.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    //Read from file and store everything in a string
    ifstream file("test.txt");
    vector<string> tokens;

    if (!file.is_open())
    {
        cerr << "Error: File not found" << endl;
        return 1;
    }

    cout << "File opened successfully" << endl;
    
    string line;
    Tokenizer tokenizer;

    while(getline(file, line)) {
        tokenizer.tokenizeInput(line);
        vector<string> lineTokens = tokenizer.getTokens();
        tokens.insert(tokens.end(), lineTokens.begin(), lineTokens.end());
    }
    //test statement print the lines read from the file
    // cout << "\nMain:" << endl;
    // for (const auto& token : tokens) {
    //     cout << token << " ";
    // }
    // Create a parser object
    Parser parser(tokens);

    if(parser.validateInput()){
        parser.evaluateExpression();
        cout << "\n" << parser.returnResult() << endl;
        cout << "Input is valid" << endl;
    }else{
        cout << "Input is invalid" << endl;
    }

    file.close();
    return 0;
}
