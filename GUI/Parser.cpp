#include "Parser.h"
#include <stdexcept>
#include <iostream>


Parser::Parser(std::vector<Token> t) {
    tokens = t;
    currentIndex = 0;
}


Token Parser::currentToken() {
    if (currentIndex >= tokens.size())
        return {TokenType::ENDFILE, "EOF"};
    return tokens[currentIndex];
}


void Parser::advance() {
    if (currentIndex < tokens.size())
        currentIndex++;
}


void Parser::expect(TokenType type) {
    if (currentToken().type != type) {
        throw std::runtime_error(
            "Syntax Error: expected " + tokenTypeToString(type) +
            " but found " + tokenTypeToString(currentToken().type)
        );
    }
    advance();
}

////////////////////////////////  RULES   /////////////////////////////////////


// exp → simple-exp [comparison-op simple-exp] 
ASTNode* Parser::exp() {

    // Parse left side (simple-exp)
    ASTNode* left = simpleExp();
  

    // Check for optional comparison operator
    TokenType t = currentToken().type;

    if (t == TokenType::LESSTHAN || t == TokenType::EQUAL) {
        // comparison-op node
        std::string opSymbol = currentToken().lexeme;
        advance();

        ASTNode* compNode = new ASTNode("op", "("+opSymbol+")");
        compNode->children.push_back(left);             // left operand
        ASTNode* right = simpleExp();
        compNode->children.push_back(right);            // right operand

        return compNode;  // return comp-op node as root
    }

    return left;
}


// assign-stmt → identifier := exp
ASTNode* Parser::assignStmt() {
    
    // id
    std::string idName = currentToken().lexeme;
    expect(TokenType::ID);

    // Create node for assignment
    ASTNode* assignNode = new ASTNode("assign","("+idName+")"); 

    // :=
    expect(TokenType::ASSIGN);

    // exp
    ASTNode* expr = exp();
    assignNode->children.push_back(expr);

    return assignNode;
}


// stmt-sequence → statement { ; statement }
ASTNode* Parser::stmtSequence() {

    // Parse the first statement
    ASTNode* first = statement();
    ASTNode* current = first;

    // Parse subsequent statements after semicolons
    while (currentToken().type == TokenType::SEMICOLON) {
        advance(); // consume ';'
        ASTNode* next = statement();

        // Attach next statement as a child of the previous statement
        current->children.push_back(next);

        current = next; // move forward for chaining
    }

    return first;
}




ASTNode* Parser::program() {
    return stmtSequence();
}

// if-stmt → if exp then stmt-sequence [else stmt-sequence] end
ASTNode* Parser::ifStmt() {
    expect(TokenType::IF);

    ASTNode* ifNode = new ASTNode("if");

    ASTNode* cond = exp();
    ifNode->children.push_back(cond);

    expect(TokenType::THEN);

    ASTNode* thenPart = stmtSequence();
    ifNode->children.push_back(thenPart);

    if (currentToken().type == TokenType::ELSE) {
        advance();
        ASTNode* elsePart = stmtSequence();
        ifNode->children.push_back(elsePart);
    }

    expect(TokenType::END);
    return ifNode;
}

// repeat-stmt → repeat stmt-sequence until exp
ASTNode* Parser::repeatStmt() {
    expect(TokenType::REPEAT);

    ASTNode* repeatNode = new ASTNode("repeat");

    ASTNode* body = stmtSequence();
    repeatNode->children.push_back(body);

    expect(TokenType::UNTIL);

    ASTNode* cond = exp();
    repeatNode->children.push_back(cond);

    return repeatNode;
}


// read-stmt → read identifier
ASTNode* Parser::readStmt() {
    expect(TokenType::READ);

    std::string idName = currentToken().lexeme;
    expect(TokenType::ID);

    return new ASTNode("read", "(" + idName + ")");
}

// write-stmt → write exp
ASTNode* Parser::writeStmt() {
    expect(TokenType::WRITE);

    ASTNode* writeNode = new ASTNode("write");
    ASTNode* e = exp();

    writeNode->children.push_back(e);
    return writeNode;
}





// statement → if-stmt | repeat-stmt | assign-stmt | read-stmt | write-stmt
ASTNode* Parser::statement() {
    Token t = currentToken();

    switch (t.type) {
        case TokenType::IF:     return ifStmt();
        case TokenType::REPEAT: return repeatStmt();
        case TokenType::ID:     return assignStmt();
        case TokenType::READ:   return readStmt();
        case TokenType::WRITE:  return writeStmt();
        default:
            throw std::runtime_error("Syntax Error: unexpected token in statement: " +
                                     tokenTypeToString(t.type));
    }
}




////////////////////// EXPRESSIONS //////////////////////

// term → factor { mulop factor }
ASTNode* Parser::term() {
    ASTNode* left = factor();

    while (currentToken().type == TokenType::MULT ||
           currentToken().type == TokenType::DIV) {

        std::string op = currentToken().lexeme;
        advance();

        ASTNode* opNode = new ASTNode("op", "("+op+")");
        opNode->children.push_back(left);

        ASTNode* right = factor();
        opNode->children.push_back(right);

        left = opNode;
    }

    return left;
}


// factor → ( exp ) | number | identifier
ASTNode* Parser::factor() {
    Token t = currentToken();

    if (t.type == TokenType::OPENBRACKET) {
        advance();
        ASTNode* e = exp();
        expect(TokenType::CLOSEDBRACKET);
        return e;
    }

    if (t.type == TokenType::NUMBER) {
        advance();
        return new ASTNode("const", "(" + t.lexeme + ")");
    }

    if (t.type == TokenType::ID) {
        advance();
        return new ASTNode("id", "(" + t.lexeme + ")");
    }

    throw std::runtime_error("Syntax Error: invalid factor: " +
                             tokenTypeToString(t.type));
}


// simple-exp → term { addop term }
ASTNode* Parser::simpleExp() {
    ASTNode* left = term();

    while (currentToken().type == TokenType::PLUS ||
           currentToken().type == TokenType::MINUS) {

        std::string op = currentToken().lexeme;
        advance();

        ASTNode* opNode = new ASTNode("op", "("+op+")");
        opNode->children.push_back(left);

        ASTNode* right = term();
        opNode->children.push_back(right);

        left = opNode; // result becomes the new left
    }

    return left;
}



// ======== parse() =========
ASTNode* Parser::parse() {
    return program();
}

