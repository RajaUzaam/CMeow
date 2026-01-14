#include "token.h"

const char* TokenTypeString[] = {
    // Single-character tokens.
    "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE", "NEWLINE",
    "COMMA", "DOT", "MINUS", "PLUS", "COLON", "SEMICOLON", "SLASH", "STAR", "UP_ARR",
    "FOE",

    // One or two character tokens.
    "BANG", "BANG_EQUAL",
    "ASSIGN", "EQUAL",
    "GREATER", "GREATER_EQUAL",
    "LESS", "LESS_EQUAL",

    // Literals.
    "IDENTIFIER", "STRING", "INTEGER", "REAL", "CHARACTER", "BOOL", "CONSTANT",

    // Keywords.
    "DECLARE", "THEN", "AND", "CLASS", "ELSE", "FUNCTION", "ENDFUNCTION", "PROCEDURE",
    "ENDPROCEDURE", "TO", "OF", "NEXT", "UNTIL", "CALL",
    "FOR", "IF", "ENDIF", "OR", "NOT", "SWITCH", "CASE", "OTHERWISE", "REPEAT", "DO",
    "OUTPUT", "INPUT", "RETURN", "SUPER", "THIS", "VAR", "WHILE", "ENDWHILE", 
    "BREAK", "ENDSWITCH", "RETURNS", "NONE"
};

void ObjString(Object obj, char buffer[][256]) {
    //char buffer[256];
    switch (obj.type) {
        case I: sprintf(*buffer, "%lli", obj.value.i); break;
        case R: sprintf(*buffer, "%f", obj.value.r); break;
        case S: sprintf(*buffer, "%s", obj.value.s); break;
        case B: sprintf(*buffer, "%i", obj.value.b); break;
        case C: sprintf(*buffer, "%c", obj.value.c); break;
        default: return;
    }
    //return buffer;
}

void MakeToken(Token* token, TokenType type, char* lexeme, Object literal, uint64_t line) {
    token->type = type;
    token->lexeme = lexeme;
    token->literal = literal;
    token->line = line;
}

char* ToString(Token* token) {
    char* str; 
    strcat(str, TokenTypeString[token->type]);
    strcat(str, ", ");
    strcat(str, token->lexeme);
    return str;
}