#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <cctype>  // For isdigit, isspace
#include <stdexcept>  // For std::invalid_argument


using namespace std;

class Tokenizer {
private:
    vector<string> tokens;
    string result;

public:

    // default constructor
    Tokenizer();

    // Tokenize the input string and store the tokens in the 'tokens' member variable
    void tokenizeInput(const string& input);

    void validateTokens();


    // Get the tokens
    vector<string> getTokens() const;

    string getResult() const {
        return result;
    }
};
    // default constructor
    Tokenizer::Tokenizer() : result("") {}


void Tokenizer::tokenizeInput(const string& input) {
    istringstream iss(input);
    string token;
    char ch;
    while (iss.get(ch)) {
        if (isspace(ch)) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else if (isalnum(ch) || ch == '_') { // Include underscore for identifiers
            token += ch;
        } else {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(string(1, ch));
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }

    //test statement print the lines read from the file
    // for (const auto& token : tokens) {
    //     cout << token << " ";
    // }
}


void Tokenizer::validateTokens() {
    // Check the tokens if presented in binary operation ex: 1 + 2
    switch (tokens.size()) {
        case 0:
            throw invalid_argument("No tokens found");
        case 1:
            throw invalid_argument("Only one token found");
        case 2:
            throw invalid_argument("Only two tokens found");
        case 3:
            if (tokens[1] != "+" && tokens[1] != "-" && tokens[1] != "*" && tokens[1] != "/") {
                throw invalid_argument("Invalid operator");
            }
            break;

        default:
            break;
    }

}


// Get the tokens
vector<string> Tokenizer::getTokens() const {
    return tokens;
}