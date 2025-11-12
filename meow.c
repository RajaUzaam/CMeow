#include "vm.h"
#include "assembler.h"

int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        perror("\nBytecode Filename not provided!");
    }

    //Assembler
    FILE* bc_file = fopen(argv[1], "r");
    ExecuteAssembler(bc_file);
    fclose(bc_file);

    //Bin Loader
    code = _code;
    code_size = _code_size;
    co_consts = _co_consts;
    co_consts_size = _co_consts_size;
    ip = _entry_point;

    //Virtual Machine
    ExecuteVM();

    return 0;
}
