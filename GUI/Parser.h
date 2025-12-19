#pragma once

#include <vector>
#include <string>
#include "Scanner.h"
#include "ASTNode.h"

class Parser {
private:
    std::vector<Token> tokens;
    int currentIndex;

    Token currentToken();
    void advance();
    void expect(TokenType type);
    Token peekNext();
    void validateSequence();

    // ===== Grammar methods =====
    ASTNode* program();
    ASTNode* stmtSequence();
    ASTNode* statement();
    ASTNode* ifStmt();
    ASTNode* repeatStmt();
    ASTNode* assignStmt();      // (implemented in Parser.cpp)
    ASTNode* readStmt();
    ASTNode* writeStmt();
    ASTNode* exp();
    ASTNode* simpleExp();
    ASTNode* term();
    ASTNode* factor();
    ASTNode* comparisonOp();
    ASTNode* addOp();
    ASTNode* mulOp();

public:
    Parser(std::vector<Token> t);
    ASTNode* parse();
};
