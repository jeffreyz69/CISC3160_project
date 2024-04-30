#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <functional>
#include <map>
#include <stdexcept>
#include <sstream>
#include "Parser.hpp"

using namespace std;

//TODO refine logic where it throws an syntax error if one line is not complete ex x = 5 + 10 (missing ;)
//Currently there is a bug where if given x = 5 followed by y = 10; it will not throw an error because y = 10; is a complete statement
//Parser should throw an error since x = 5 is not a complete statement
bool Parser::validateInput() {
    stack<char> parentheses;
    bool expectIdentifier = true, expectOperatorOrEquals = false, expectValue = false, expectOpenParenthesis = false;

    for (const auto& token : tokens) {
        // Check if the token is an identifier example, x, y, z or a number
        if (expectIdentifier) {
            if (!token.empty() && isalpha(token[0])) {
                expectIdentifier = false;
                expectOperatorOrEquals = true;
            } else {
                cerr << "Error: Expected identifier, found '" << token << "'." << endl;
                return false;
            }
        // Check if the token is an operator or equals sign 
        } else if (expectOperatorOrEquals) {
            if (token == "=") {
                expectValue = true;
                expectOperatorOrEquals = false;
                expectOpenParenthesis = true;
            // Check if the token is an operator 
            } else if (token == "+" || token == "-" || token == "*" || token == "/") {
                expectIdentifier = true; // Expect another identifier or number after an operator
                expectOpenParenthesis = true; // An open parenthesis could also follow
            } else if (token == ";") {
                if (!parentheses.empty()) {
                    cerr << "Error: Unmatched parentheses." << endl;
                    return false;
                }
                if (tokens.back() != token) { // Check if it's not the last token
                    expectIdentifier = true; // Reset for a potential new statement
                }
                expectOperatorOrEquals = false;
                expectValue = false; // Reset all expectations
            } else if (token == ")") {
                if (parentheses.empty()) {
                    cerr << "Error: Unmatched parentheses." << endl;
                    return false;
                }
                parentheses.pop();
                expectOperatorOrEquals = true; // Expect something after the closing parenthesis
            } else {
                cerr << "Error: Expected operator, '=', ')', or ';', found '" << token << "'." << endl;
                return false;
            }
        } else if (expectValue) {
            if (token == "(") {
                parentheses.push('(');
                expectOpenParenthesis = false; // Reset since we have an open parenthesis
                expectValue = true; // Still expecting a value or identifier after '('
            } else if (!token.empty() && (isdigit(token[0]) || isalpha(token[0]))) {
                expectValue = false;
                expectOperatorOrEquals = true; // Could be followed by an operator or end of expression
                expectOpenParenthesis = false;
            } else {
                cerr << "Error: Expected value, identifier, or '(', found '" << token << "'." << endl;
                return false;
            }
        }
    }

    if (!parentheses.empty()) {
        cerr << "Error: Unmatched parentheses at the end of input." << endl;
        return false;
    }

    if (expectIdentifier && !expectOperatorOrEquals && tokens.back() == ";") {
        return true; // The last token is a semicolon, so the input is valid if all other conditions are met
    } else if (expectIdentifier && !expectOperatorOrEquals) {
        cerr << "Error: Incomplete statement at end of input." << endl;
        return false;
    }

    return true;
}

void Parser::evaluateExpression() {
    if (tokens.empty()) throw std::invalid_argument("Expression is empty");

    stack<int> valueStack;
    stack<string> operatorStack;
    map<string, int> precedence = {{"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}}; // Operator precedence
    auto applyOperation = [&valueStack](char op) {
        if (valueStack.size() < 2) return;
        int b = valueStack.top(); valueStack.pop();
        int a = valueStack.top(); valueStack.pop();
        switch (op) {
            case '+': valueStack.push(a + b); break;
            case '-': valueStack.push(a - b); break;
            case '*': valueStack.push(a * b); break;
            case '/': valueStack.push(a / b); break;
        }
    };

    string identifier;
    for (int i = 0; i < tokens.size(); i++) {
        const string& token = tokens[i];

        if (isalpha(token[0])) { // Identifier or variable
            if (i + 1 < tokens.size() && tokens[i + 1] == "=") {
                identifier = token; // Assignment to a variable
                i++; // skip '=' token
            } else { // Part of an expression
                if (symbolTable.find(token) != symbolTable.end()) {
                    valueStack.push(symbolTable[token]);
                } else {
                    throw runtime_error("Undefined variable used in expression: " + token);
                }
            }
        } else if (isdigit(token[0])) { // Numeric literal
            valueStack.push(stoi(token));
        } else if (token == "(") {
            operatorStack.push(token);
        } else if (token == ")") {
            while (!operatorStack.empty() && operatorStack.top() != "(") {
                applyOperation(operatorStack.top()[0]);
                operatorStack.pop();
            }
            operatorStack.pop(); // pop '('
        } else if (token == "+" || token == "-" || token == "*" || token == "/") {
            while (!operatorStack.empty() && precedence[operatorStack.top()] >= precedence[token]) {
                applyOperation(operatorStack.top()[0]);
                operatorStack.pop();
            }
            operatorStack.push(token);
        } else if (token == ";") {
            while (!operatorStack.empty()) {
                applyOperation(operatorStack.top()[0]);
                operatorStack.pop();
            }
            if (!identifier.empty() && !valueStack.empty()) {
                symbolTable[identifier] = valueStack.top();
                valueStack.pop();
            }
            identifier.clear(); // Reset for the next statement
        }
    }
}

// Return the result of the evaluation from the symbol table
// example: x = 5; y = 10; z = x + y; return z;
string Parser::returnResult() const{
    stringstream ss;
    for (const auto& pair : symbolTable) {
        ss << pair.first << " = " << pair.second << "\n";  // Format: key = value
    }
    // test return map size
    cout << "Map size: " << symbolTable.size() << endl;
    return ss.str();
}