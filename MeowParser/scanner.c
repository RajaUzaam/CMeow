#include "scanner.h"
#include "file_handler.h"

static char* src_code;
static uint64_t src_len;

Token* tokens = NULL;
uint64_t token_num = 0;

static uint64_t start = 0;
static uint64_t current = 0;
static uint64_t line = 1;

bool error_status = false;

static char next() {
    return src_code[++current - 1];
}

static char peek() {
    return src_code[current];
}

static char peekNext() {
    return src_code[current+1];
}

static bool FileEnd() {
    return current >= src_len;
}

static bool match(char expected) {
    if (FileEnd()) return false;
    else if (peek() != expected) return false;
    next(); 
    return true;
}

static void AddToken(Token token) {
    tokens = realloc(tokens, sizeof(Token) * (token_num+1));
    tokens[token_num++] = token;
}

typedef struct {
    char key_name[15];
    int keyword;
    UT_hash_handle hh;
} Keyword;

static Keyword* keywords = NULL;

static void InitializeKeyWordHash() {
    for (int i = STRING; i <= NONE; i++) {
        Keyword* keyword = malloc(sizeof(Keyword));
        keyword->keyword = i;
        strcpy(keyword->key_name, TokenTypeString[i]);
        HASH_ADD_STR(keywords, key_name, keyword);
    }
}

static void add_identifier() {
    while (isalnum(peek()) || peek() == '_') next();
    char* substr = sub_str(&src_code, start, current - start, src_len);
    Keyword* kw;
    HASH_FIND_STR(keywords, substr, kw);
    if (kw == NULL) {
        if (!strcmp(substr, "TRUE")) {AddToken((Token) {.type=BOOL, .literal={.type=B, .value=true}, .line=line});}
        else if (!strcmp(substr, "FALSE")) {AddToken((Token) {.type=BOOL, .literal={.type=B, .value=false}, .line=line});}
        else {AddToken((Token) {.type=IDENTIFIER, .lexeme=substr, .line=line});}
    } else {
        AddToken((Token) {.type=kw->keyword, .line=line});
    }
}

static void ScanToken() {
    char c = next();
    switch (c) {
        case '+': AddToken((Token) {.type=PLUS, .lexeme="+", .line=line}); break;
        case '*': AddToken((Token) {.type=STAR, .lexeme="*", .line=line}); break;
        case '-': AddToken((Token) {.type=MINUS, .lexeme="-", .line=line}); break;
        case '(': AddToken((Token) {.type=LEFT_PAREN, .lexeme="(", .line=line}); break;
        case ')': AddToken((Token) {.type=RIGHT_PAREN, .lexeme=")", .line=line}); break;
        case '[': AddToken((Token) {.type=LEFT_BRACE, .lexeme="[", .line=line}); break;
        case ']': AddToken((Token) {.type=RIGHT_BRACE, .lexeme="]", .line=line}); break;
        case ':': AddToken((Token) {.type=COLON, .lexeme=":", .line=line}); break;
        case ';': AddToken((Token) {.type=SEMICOLON, .lexeme=";", .line=line}); break;
        case '=': AddToken((Token) {.type=EQUAL, .lexeme="=", .line=line}); break;
        case '.': AddToken((Token) {.type=DOT, .lexeme=".", .line=line}); break;
        case '<':
            AddToken((Token) {.type=(match('=') ? LESS_EQUAL : (match('-') ? ASSIGN: LESS)), .lexeme=sub_str(&src_code, start, current-start, src_len)}); break;
        case '>': 
            AddToken((Token) {.type=(match('=') ? GREATER_EQUAL : GREATER), .lexeme=sub_str(&src_code, start, current-start, src_len)}); break;
        case '!': 
            AddToken((Token) {.type=(match('=') ? BANG_EQUAL : BANG), .lexeme=sub_str(&src_code, start, current-start, src_len)}); break;
        case '/':
            if (match('/')) {
                while (!FileEnd() && peek() != '\n') next();
            } else if (match('*')) {
                while (!FileEnd() && !(peek() == '*' && peekNext() == '/')) next();
                current += 2;
            } else {
                AddToken((Token) {.type=SLASH, .line=line, .lexeme="/"});
            }
            break;
        case '\"': 
            next();
            if (is_str(&src_code, &current, src_len, FileEnd, peek, &line)) {
                char* substr = sub_str(&src_code, start+1, current-start-2, src_len);
                AddToken((Token) {.type=STRING, .line=line, .literal.value.s = substr, .literal.type=S});
            } else {
                SimpleError(&error_status, "Unterminated String!", line);
            }
            break;
        case ' ': case '\t': case '\r': break;
        case '\n':
            if (tokens[token_num-1].type != NEWLINE) {
                AddToken((Token) {.line=line, .lexeme="\\n", .type=NEWLINE});
            }
            line++; break;
        default:
            if (isdigit(c) && is_int(&src_code, &current, FileEnd, peek, &line)) {
                char* substr = sub_str(&src_code, start, current-start+1, src_len);
                AddToken((Token) {.type=INTEGER, .literal.type=I, .literal.value.i=_atoi64(substr), .line=line});
            } else if (isalpha(c) || c == '_') {
                add_identifier();
            } else {
                Error(&error_status, line, 0, SYNTAX_ERROR, (char[]) { c, '\0'} );
            }
            break;
    }
}

void Scanner(char* file_name, Token** out_tokens, uint64_t* out_token_num) {
    Read(file_name, &src_code, &src_len);
    InitializeKeyWordHash();
    while (!FileEnd()) {
        ScanToken();
        start = current;
    }
    AddToken((Token) {.lexeme="FOE", .type=FOE, .line=line});
    for (int x = 0; x < token_num-1; x++) {
        printf("%s>%s< -> ", TokenTypeString[tokens[x].type], tokens[x].lexeme);
    }
    printf("%s\n", TokenTypeString[tokens[token_num-1].type]);
    *out_tokens = tokens;
    *out_token_num = token_num;
    return;
}