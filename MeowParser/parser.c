#include "parser.h"

static Expr* expression();
Expr* declaration();
Stmt* statement();

static Token* tokens;
static uint64_t curr = 0;

static Token peek() {
    return tokens[curr];
} 

static bool isAtEnd() {
    return peek().type == FOE;
}

static Token previous() {
    return tokens[curr-1];
}

static Token advance() {
    if (!isAtEnd()) curr++;
    return previous();
}

static bool check(TokenType type) {
    if (isAtEnd()) return false;
    return peek().type == type;
}

static bool match(TokenType types[], int types_num) {
    for (int i = 0; i < types_num; i++) {
        if (check(types[i])) {
            advance();
            return true;
        }
    }
    return false;
}

Token consume(TokenType type, char* message) {
    if (check(type)) return advance();
    printf("%s\n", message); exit(1);
}

static Expr* alloc_expr(Expr e) {
    Expr* p = malloc(sizeof(Expr));
    *p = e;
    return p;
}

static Stmt* alloc_stmt(Stmt e) {
    Stmt* p = malloc(sizeof(Stmt));
    *p = e;
    return p;
}

Expr* primary() {
    if (match((TokenType[]){INTEGER, REAL, STRING, BOOL}, 4)) {
        return alloc_expr((Expr){.type=LITERAL, .literal=previous().literal});
    }
    if (match((TokenType[]){LEFT_PAREN}, 1)) {
        Expr* expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after expression.");
        return alloc_expr((Expr){.type=GROUPING, .group=expr});
    }
    printf("Expected expression\n");
    exit(1);
}

Expr* unary() {
    if (match((TokenType[]) {BANG, MINUS}, 2)) {
        Token operator = previous();
        Expr* right = unary();
        return alloc_expr((Expr){.type=UNARY, .unary={.right=right, .type=operator}});
    }
    return primary();
}

Expr* factor() {
    Expr* expr = unary();
    while (match((TokenType[]){SLASH, STAR}, 2)) {
        Token operator = previous();
        Expr* right = unary();
        expr = alloc_expr((Expr){.type=BINARY, .binary={.left=expr, .right=right, .type=operator}});
    }
    return expr;
}

Expr* term() {
    Expr* expr = factor();
    while (match((TokenType[]){MINUS, PLUS}, 2)) {
        Token operator = previous();
        Expr* right = factor();
        expr = alloc_expr((Expr){.type=BINARY, .binary={.left=expr, .right=right, .type=operator}});
    }
    return expr;
}

Expr* comparsion() {
    Expr* expr = term();
    while (match((TokenType[]){GREATER, GREATER_EQUAL, LESS, LESS_EQUAL}, 4)) {
        Token operator = previous();
        Expr* right = term();
        expr = alloc_expr((Expr){.type=BINARY, .binary={.left=expr, .right=right, .type=operator}});
    }
    return expr;
}

Expr* equality() {
    Expr* expr = comparsion();
    while (match((TokenType[]){BANG_EQUAL, EQUAL}, 2)) {
        Token operator = previous();
        Expr* right = comparsion();
        expr = alloc_expr((Expr){.type=BINARY, .binary={.left=expr, .right=right, .type=operator}});
    }
    return expr;
}

Expr* expression() {
    return equality();
}

Expr* declaration() {

}

Stmt* print_statement() {
    Expr* value = expression();
    consume(NEWLINE, "Expected a new line at the end");
    return alloc_stmt((Stmt) {.type=PRINT, .out_stmt=value});
}

Stmt* expression_statement() {
    Expr* value = expression();
    consume(NEWLINE, "Expected a new line at the end");
    return alloc_stmt((Stmt) {.type=EXPR, .out_stmt=value});
}

Stmt* statement() {
    if (match((TokenType[]) {OUTPUT}, 1)) {
        return print_statement();
    }
    return expression_statement();
}

void add_statement(Stmt*** stmts, uint32_t* stmt_num, Stmt* add_stmt) {
    *stmts = realloc(*stmts, sizeof(Stmt) * (*stmt_num + 1));
    (*stmts)[*stmt_num] = add_stmt;
    (*stmt_num)++;
}

//Stmt** statements = NULL;

void Parser(Token** toks, Stmt*** statements, uint32_t* stmts_num) {
    tokens = *toks;
    curr = 0;
    *stmts_num = 0;

    while (!isAtEnd()) {
        add_statement(statements, stmts_num, statement());
    }
    return;
}
