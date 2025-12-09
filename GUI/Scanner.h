#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>
#include <map>

// =======================
//      Token Types
// =======================
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

// =======================
//      Token Struct
// =======================
struct Token
{
    TokenType type;
    std::string lexeme;
};

// =======================
//  Reserved Keywords Map
// =======================

extern std::map<std::string, TokenType> reservedKeywords;

// =======================
//    Global Error String
// =======================

extern std::string scannerErrorMessage;

// =======================
//   Utility Declarations
// =======================

std::string tokenTypeToString(TokenType type);

std::string readFile(const std::string &filename);

void writeFile(const std::string &filename, const std::vector<Token> &tokens);

// =======================
//     Scanner Function
// =======================

std::vector<Token>scan(const std::string &sourceCode);

#endif // SCANNER_H
