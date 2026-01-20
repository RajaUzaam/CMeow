#ifndef TOKENS
#define TOKENS

#include "header.h"
#include "../MeowObjs/objects.h"

typedef enum {
    // Single-character tokens.
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, NEWLINE,
    COMMA, DOT, MINUS, PLUS, COLON, SEMICOLON, SLASH, STAR, UP_ARR, FOE,

    // One or two character tokens.
    BANG, BANG_EQUAL,
    ASSIGN, EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // Literals.
    IDENTIFIER, 
    
    // Literals and Keywords
    STRING, INTEGER, REAL, CHARACTER, BL, CONSTANT,

    // Keywords.
    DECLARE, THEN, AND, CLASS, ELSE, FUNCTION, ENDFUNCTION, PROCEDURE, ENDPROCEDURE,
    TO, OF, NEXT, UNTIL, TOK_CALL,
    FOR, IF, ENDIF, OR, NOT, SWITCH, CASE, OTHERWISE, REPEAT, DO,
    OUTPUT, INPUT, RETURN, SUPER, THIS, VAR, WHILE, ENDWHILE, 
    BREAK, ENDSWITCH, RETURNS, NUL
} TokenType;

// typedef struct {
//     enum {I, R, S, B, C, N} type;
//     union {
//         int64_t i;
//         double r;
//         char* s;
//         bool b;
//         char c;
//     } value;
// } Object;

typedef struct {
    TokenType type;
    char* lexeme;
    Value literal;
    uint64_t line;
} Token;

extern const char* TokenTypeString[];

#endif

// void ObjString(Object obj, char buffer[][256]);
// void MakeToken(Token* token, TokenType type, char* lexeme, Object literal, uint64_t line);
char* ToString(Token* token);