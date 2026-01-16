#include "main.h"

bool err_status = false;

int main(int argc, char* argv[]) {
    if (argc > 2) {
        printf("Usage [Meow]\n"); return 0;
    } else if (argc < 2) {
        printf("FileName need!\n"); return 0;
    }

    Token* tokens;
    uint64_t tokens_num;
    Scanner(argv[1], &tokens, &tokens_num);
    
    uint32_t stmts_num = 0;
    Stmt** tree = NULL;
    Parser(&tokens, &tree, &stmts_num);
    
    Walker(&tree, stmts_num);

    if (err_status) {
        exit(1);
    }
    return 0;
}