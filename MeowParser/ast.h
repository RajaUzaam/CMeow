#ifndef AST
#define AST

#include "header.h"
#include "token.h"
#include "error.h"

typedef struct Expr Expr;
typedef struct Stmt Stmt;

typedef enum {
    BINARY,
    GROUPING,
    LITERAL,
    UNARY
} ExprType;

typedef struct {
    Token type;
    Expr* left;
    Expr* right;
} Binary;

typedef struct {
    Expr* expression;
} Grouping;

typedef struct {
    Token type;
    Expr* right;
} Unary;

struct Expr {
    ExprType type;
    union {
        Binary binary;
        Grouping group;
        Object literal;
        Unary unary;
    };
};

typedef enum StmtType {
    EXPR,
    PRINT 
} StmtType;

struct Stmt {
    StmtType type;
    union {
        Expr* expr;
        Expr* out_stmt;
    };
};

#endif

//void GenAST();
void PrintAST(Expr* e);