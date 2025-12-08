#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <map>

using namespace std;

// Define an enum for token types
enum class TokenType
{
    IF,
    THEN,
    ELSE,
    END,
    REPEAT,
    UNTIL,
    READ,
    WRITE,
    SEMICOLON,
    ASSIGN,
    ID,
    ENDFILE,
    ERROR,
    LESSTHAN,
    EQUAL,
    PLUS,
    MINUS,
    MULT,
    DIV,
    OPENBRACKET,
    CLOSEDBRACKET,
    NUMBER
};

// Structure to represent a token
struct Token
{
    TokenType type;
    string lexeme;
};

// Map of reserved keywords
map<string, TokenType> reservedKeywords = {
    {"if", TokenType::IF},
    {"then", TokenType::THEN},
    {"else", TokenType::ELSE},
    {"end", TokenType::END},
    {"repeat", TokenType::REPEAT},
    {"until", TokenType::UNTIL},
    {"read", TokenType::READ},
    {"write", TokenType::WRITE} };

// Helper function to print token type (for demonstration)
string tokenTypeToString(TokenType type)
{
    switch (type)
    {
    case TokenType::IF:         return "IF";
    case TokenType::THEN:       return "THEN";
    case TokenType::ELSE:       return "ELSE";
    case TokenType::END:        return "END";
    case TokenType::REPEAT:     return "REPEAT";
    case TokenType::UNTIL:      return "UNTIL";
    case TokenType::READ:       return "READ";
    case TokenType::WRITE:      return "WRITE";
    case TokenType::SEMICOLON:  return "SEMICOLON";
    case TokenType::ASSIGN:     return "ASSIGN";
    case TokenType::ID:         return "ID";
    case TokenType::ENDFILE:    return "ENDFILE";
    case TokenType::ERROR:      return "ERROR";
    case TokenType::LESSTHAN:   return "LESSTHAN";
    case TokenType::EQUAL:      return "EQUAL";
    case TokenType::PLUS:       return "PLUS";
    case TokenType::MINUS:      return "MINUS";
    case TokenType::MULT:       return "MULT";
    case TokenType::DIV:        return "DIV";
    case TokenType::OPENBRACKET: return "OPENBRACKET";
    case TokenType::CLOSEDBRACKET: return "CLOSEDBRACKET";
    case TokenType::NUMBER:     return "NUMBER";
    default:                    return "UNKNOWN";
    }
}

// Global variable to store the error message
string scannerErrorMessage = "";

// The scanner function, now stopping on error and clearing the tokens vector
vector<Token> scan(const string& sourceCode)
{
    vector<Token> tokens;
    string currentLexeme;
    int i = 0;
    int n = sourceCode.length();
    scannerErrorMessage = ""; // Clear previous error message

    while (i < n)
    {
        char currentChar = sourceCode[i];

        // Skip whitespace
        if (isspace(currentChar))
        {
            i++;
            continue;
        }

        // Handle identifiers and reserved words
        else if (isalpha(currentChar))
        {
            currentLexeme = "";
            int startPos = i; // Save start position

            while (i < n && isalpha(sourceCode[i]))
            {
                currentLexeme += sourceCode[i];
                i++;
            }

            // Check if it's a reserved keyword
            if (reservedKeywords.count(currentLexeme))
            {
                tokens.push_back({ reservedKeywords[currentLexeme], currentLexeme });
            }
            else
            {
                tokens.push_back({ TokenType::ID, currentLexeme });
            }

            // Check for immediate digits after an ID
            if (i < n && isdigit(sourceCode[i])) {
                // This is generally an error in TINY, but based on your original logic:
                string numLexeme = "";
                while (i < n && isdigit(sourceCode[i])) {
                    numLexeme += sourceCode[i];
                    i++;
                }
                if (!numLexeme.empty()) {
                    tokens.push_back({ TokenType::NUMBER, numLexeme });
                }
            }
            continue;
        }

        // Handle special symbols and operators
        else if (currentChar == ':')
        {
            if (i + 1 < n && sourceCode[i + 1] == '=')
            {
                tokens.push_back({ TokenType::ASSIGN, ":=" });
                i += 2;
            }
            else
            {
                scannerErrorMessage = "Scanner Error: Expected ':=' but found ':' at position " + to_string(i) + ".";
                tokens.clear();
                return tokens;
            }
        }
        else if (currentChar == ';')
        {
            tokens.push_back({ TokenType::SEMICOLON, ";" });
            i++;
        }
        else if (currentChar == '<')
        {
            tokens.push_back({ TokenType::LESSTHAN, "<" });
            i++;
        }
        else if (currentChar == '=')
        {
            tokens.push_back({ TokenType::EQUAL, "=" });
            i++;
        }
        else if (currentChar == '+')
        {
            tokens.push_back({ TokenType::PLUS, "+" });
            i++;
        }
        else if (currentChar == '-')
        {
            tokens.push_back({ TokenType::MINUS, "-" });
            i++;
        }
        else if (currentChar == '*')
        {
            tokens.push_back({ TokenType::MULT, "*" });
            i++;
        }
        else if (currentChar == '/')
        {
            tokens.push_back({ TokenType::DIV, "/" });
            i++;
        }
        else if (currentChar == '(')
        {
            tokens.push_back({ TokenType::OPENBRACKET, "(" });
            i++;
        }
        else if (currentChar == ')')
        {
            tokens.push_back({ TokenType::CLOSEDBRACKET, ")" });
            i++;
        }
        else if (currentChar == '{') // Handle TINY comment start
        {
            // Skip the '{'
            i++;
            int startPos = i - 1;
            // Consume characters until '}' is found
            while (i < n && sourceCode[i] != '}')
            {
                i++;
            }
            // Check if we reached end of file without closing the comment
            if (i >= n)
            {
                scannerErrorMessage = "Scanner Error: Unclosed comment starting at position " + to_string(startPos) + ".";
                tokens.clear();
                return tokens;
            }
            // Skip the closing '}'
            i++;
            continue;
        }

        // Numbers
        else if (isdigit(currentChar))
        {
            currentLexeme = "";

            while (i < n && isdigit(sourceCode[i]))
            {
                currentLexeme += sourceCode[i];
                i++;
            }

            tokens.push_back({ TokenType::NUMBER, currentLexeme });
        }

        else
        {
            scannerErrorMessage = "Scanner Error: Unexpected character '" + string(1, currentChar) + "' at position " + to_string(i) + ".";
            tokens.clear();
            return tokens;
        }
    }

    // Only add ENDFILE if no error occurred
    if (tokens.empty() && scannerErrorMessage.empty()) {
        // Handle case where code is empty (or only whitespace)
        tokens.push_back({ TokenType::ENDFILE, "EOF" });
    }
    else if (!tokens.empty()) {
        tokens.push_back({ TokenType::ENDFILE, "EOF" });
    }

    return tokens;
}

// Main function to run the scanner
int main()
{
    string tinyCode = "{ Sample program in TINY language }\n"
        "read x;\n"
        "if 0 < x then\n"
        "  fact := 1;\n"
        "  repeat\n"
        "    fact := fact * x;\n"
        "    x := x - 1\n"
        "  until x = 0;\n"
        "  write fact\n"
        "end\n";


    vector<Token> tokens = scan(tinyCode);

    // Check for error condition
    if (tokens.empty() && !scannerErrorMessage.empty())
    {
        cerr << "\n--- Scanning failed---" << endl;
        cerr << scannerErrorMessage << endl;
    }
    else
    {
        cout << "Tokens produced by the scanner:" << endl;
        cout << "-------------------------------" << endl;
        for (const auto& token : tokens)
        {
            cout << "Type: " << tokenTypeToString(token.type) << " | Lexeme: \"" << token.lexeme << "\"" << endl;
        }
        cout << "-------------------------------" << endl;
    }

    return 0;
}