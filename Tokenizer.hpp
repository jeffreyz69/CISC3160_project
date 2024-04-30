#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <cctype>  // For isdigit, isspace
#include <stdexcept>  // For std::invalid_argument

class Tokenizer {
private:
    std::vector<std::string> tokens;  // Stores tokens derived from the input string
    std::string result;               // Stores the final result after evaluation

public:
    // Default constructor
    Tokenizer();

    // Tokenizes the input string and stores the tokens in 'tokens'
    void tokenizeInput(const std::string& input);

    // Validates the tokens to ensure they form a correct expression
    void validateTokens();

    // Returns the tokens
    std::vector<std::string> getTokens() const;

    // Returns the result of the expression evaluation
    std::string getResult() const;
};

#endif // TOKENIZER_HPP
