#include "Scanner.h"
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;



// Map of reserved keywords
map<string, TokenType> reservedKeywords = {
    {"if", TokenType::IF},
    {"then", TokenType::THEN},
    {"else", TokenType::ELSE},
    {"end", TokenType::END},
    {"repeat", TokenType::REPEAT},
    {"until", TokenType::UNTIL},
    {"read", TokenType::READ},
    {"write", TokenType::WRITE}};

// Helper function to print token type (for demonstration)
string tokenTypeToString(TokenType type)
{
    switch (type)
    {
    case TokenType::IF:
        return "IF";
    case TokenType::THEN:
        return "THEN";
    case TokenType::ELSE:
        return "ELSE";
    case TokenType::END:
        return "END";
    case TokenType::REPEAT:
        return "REPEAT";
    case TokenType::UNTIL:
        return "UNTIL";
    case TokenType::READ:
        return "READ";
    case TokenType::WRITE:
        return "WRITE";
    case TokenType::SEMICOLON:
        return "SEMICOLON";
    case TokenType::ASSIGN:
        return "ASSIGN";
    case TokenType::ID:
        return "ID";
    case TokenType::ENDFILE:
        return "ENDFILE";
    case TokenType::ERROR:
        return "ERROR";
    case TokenType::LESSTHAN:
        return "LESSTHAN";
    case TokenType::EQUAL:
        return "EQUAL";
    case TokenType::PLUS:
        return "PLUS";
    case TokenType::MINUS:
        return "MINUS";
    case TokenType::MULT:
        return "MULT";
    case TokenType::DIV:
        return "DIV";
    case TokenType::OPENBRACKET:
        return "OPENBRACKET";
    case TokenType::CLOSEDBRACKET:
        return "CLOSEDBRACKET";
    case TokenType::NUMBER:
        return "NUMBER";
    default:
        return "UNKNOWN";
    }
}

// Global variable to store the error message
string scannerErrorMessage = "";

// Function to read file content into a string
string readFile(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        throw runtime_error("Error: Cannot open input file '" + filename + "'");
    }

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Function to write tokens into output file
void writeFile(const string &filename, const vector<Token> &tokens)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        throw runtime_error("Error: Cannot open output file '" + filename + "'");
    }

    file << "Tokens produced by the scanner:" << endl;
    file << "-------------------------------" << endl;
    for (const auto &token : tokens)
    {
        file << "Lexeme: \"" << token.lexeme << "\"" << ", Type: " << tokenTypeToString(token.type) << endl;
    }
    file << "-------------------------------" << endl;
    file << "Total tokens: " << tokens.size() << endl;
}

// The scanner function, now stopping on error and clearing the tokens vector
vector<Token>scan(const string &sourceCode)
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

            while (i < n && isalpha(sourceCode[i]))
            {
                currentLexeme += sourceCode[i];
                i++;
            }

            // Check if it's a reserved keyword
            if (reservedKeywords.count(currentLexeme))
            {
                tokens.push_back({reservedKeywords[currentLexeme], currentLexeme});
            }
            else
            {
                tokens.push_back({TokenType::ID, currentLexeme});
            }

            // Check for immediate digits after an ID
            if (i < n && isdigit(sourceCode[i]))
            {
                // This is generally an error in TINY, but based on your original logic:
                string numLexeme = "";
                while (i < n && isdigit(sourceCode[i]))
                {
                    numLexeme += sourceCode[i];
                    i++;
                }
                if (!numLexeme.empty())
                {
                    tokens.push_back({TokenType::NUMBER, numLexeme});
                }
            }
            continue;
        }

        // Handle special symbols and operators
        else if (currentChar == ':')
        {
            if (i + 1 < n && sourceCode[i + 1] == '=')
            {
                tokens.push_back({TokenType::ASSIGN, ":="});
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
            tokens.push_back({TokenType::SEMICOLON, ";"});
            i++;
        }
        else if (currentChar == '<')
        {
            tokens.push_back({TokenType::LESSTHAN, "<"});
            i++;
        }
        else if (currentChar == '=')
        {
            tokens.push_back({TokenType::EQUAL, "="});
            i++;
        }
        else if (currentChar == '+')
        {
            tokens.push_back({TokenType::PLUS, "+"});
            i++;
        }
        else if (currentChar == '-')
        {
            tokens.push_back({TokenType::MINUS, "-"});
            i++;
        }
        else if (currentChar == '*')
        {
            tokens.push_back({TokenType::MULT, "*"});
            i++;
        }
        else if (currentChar == '/')
        {
            tokens.push_back({TokenType::DIV, "/"});
            i++;
        }
        else if (currentChar == '(')
        {
            tokens.push_back({TokenType::OPENBRACKET, "("});
            i++;
        }
        else if (currentChar == ')')
        {
            tokens.push_back({TokenType::CLOSEDBRACKET, ")"});
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

            tokens.push_back({TokenType::NUMBER, currentLexeme});
        }

        else
        {
            scannerErrorMessage = "Scanner Error: Unexpected character '" + string(1, currentChar) + "' at position " + to_string(i) + ".";
            tokens.clear();
            return tokens;
        }
    }

    // Only add ENDFILE if no error occurred
    if (tokens.empty() && scannerErrorMessage.empty())
    {
        // Handle case where code is empty (or only whitespace)
        tokens.push_back({TokenType::ENDFILE, "EOF"});
    }
    else if (!tokens.empty())
    {
        tokens.push_back({TokenType::ENDFILE, "EOF"});
    }

    return tokens;
}
// Main function with command line argument handling
// int main(int argc, char *argv[])
// {
//     // Check command line arguments
//     if (argc != 4)
//     {
//         cerr << "Usage: " << argv[0] << " <inputfile> scan <outputfile>" << endl;
//         cerr << "Please type: " << argv[0] << " inputfile scan outputfile" << endl;
//         return 1;
//     }

//     string inputFile = argv[1];
//     string command = argv[2];
//     string outputFile = argv[3];

//     // Validate command
//     if (command != "scan")
//     {
//         cerr << "Error: Unknown command '" << command << "'" << endl;
//         cerr << "Usage: " << argv[0] << " <inputfile> scan <outputfile>" << endl;
//         return 1;
//     }

//     try
//     {
//         // Read source code from input file
//         cout << "Reading source code from: " << inputFile << endl;
//         string sourceCode = readFile(inputFile);

//         // Scan the source code
//         cout << "Scanning source code..." << endl;
//         vector<Token> tokens = scan(sourceCode);

//         // Check for scanning errors
//         if (tokens.empty() && !scannerErrorMessage.empty())
//         {
//             cerr << "\n--- Scanning failed ---" << endl;
//             cerr << scannerErrorMessage << endl;
//             return 1;
//         }

//         // Write tokens to output file
//         cout << "Writing tokens to: " << outputFile << endl;
//         writeFile(outputFile, tokens);

//         // Also display success message on console
//         cout << "\n--- Scanning completed successfully ---" << endl;
//         cout << "Total tokens generated: " << tokens.size() << endl;
//         cout << "Tokens written to: " << outputFile << endl;
//     }
//     catch (const exception &e)
//     {
//         cerr << "Error: " << e.what() << endl;
//         return 1;
//     }

//     return 0;
// }
