#pragma once
#include <string>
#include <vector>

struct ASTNode {
    std::string type;                  // "AssignStmt", "Identifier", "Exp",....
    std::string value;                 // value of token if leaf node
    std::vector<ASTNode*> children;    // subtrees

    ASTNode(std::string t, std::string v = "")
        : type(t), value(v) {}
};
