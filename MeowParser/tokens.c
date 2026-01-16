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
    "IDENTIFIER", "STRING", "INTEGER", "REAL", "CHARACTER", "BL", "CONSTANT",

    // Keywords.
    "DECLARE", "THEN", "AND", "CLASS", "ELSE", "FUNCTION", "ENDFUNCTION", "PROCEDURE",
    "ENDPROCEDURE", "TO", "OF", "NEXT", "UNTIL", "CALL",
    "FOR", "IF", "ENDIF", "OR", "NOT", "SWITCH", "CASE", "OTHERWISE", "REPEAT", "DO",
    "OUTPUT", "INPUT", "RETURN", "SUPER", "THIS", "VAR", "WHILE", "ENDWHILE", 
    "BREAK", "ENDSWITCH", "RETURNS", "NUL"
};

void ObjString(Value obj, char buffer[][256]) {
    //char buffer[256];
    switch (obj.type) {
        case INT32: sprintf(*buffer, "%lli", obj.value.i32); break;
        case REAL32: sprintf(*buffer, "%f", obj.value.r32); break;
        case OBJ: if (obj.type == STR) {sprintf(*buffer, "%s", obj.value.obj.str_obj.str);}; break;
        case BOOL: sprintf(*buffer, "%i", obj.value.bl); break;
        case CHAR: sprintf(*buffer, "%c", obj.value.chr); break;
        default: return;
    }
    //return buffer;
}

void MakeToken(Token* token, TokenType type, char* lexeme, Value literal, uint64_t line) {
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