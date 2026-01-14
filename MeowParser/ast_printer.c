#include "ast.h"

void PrintAST(Expr* e); // forward declaration

// parenthesize helper for nodes with children
void parenthesize(const char* name, Expr* left, Expr* right) {
    printf("(%s ", name);
    PrintAST(left);
    if (right) { 
        printf(" ");
        PrintAST(right);
    }
    printf(")");
}

// Node-specific printing functions
void print_binary(Expr* e) {
    parenthesize(e->binary.type.lexeme, e->binary.left, e->binary.right);
}

void print_unary(Expr* e) {
    parenthesize(e->unary.type.lexeme, e->unary.right, NULL);
}

void print_grouping(Expr* e) {
    parenthesize("group", e->group.expression, NULL);
}

void print_literal(Expr* e) {
    char lit[256]; 
    ObjString(e->literal, &lit);
    printf("%s", lit); // leaf node, no children
}

// Main dispatcher (like Java accept/visit)
void PrintAST(Expr* e) {
    if (!e) return;

    switch (e->type) {
        case BINARY:   print_binary(e);   break;
        case UNARY:    print_unary(e);    break;
        case GROUPING: print_grouping(e); break;
        case LITERAL:  print_literal(e);  break;
    }
}