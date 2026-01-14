#include "header.h"
#include "instruction_set.h"
#include "MeowVM/vm.h"
#include "MeowASM/assembler.h"

int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        perror("\nBytecode Filename not provided!");
    }

    //Assembler
    FILE* bc_file = fopen(argv[1], "r");
    ExecuteAssembler(bc_file);
    fclose(bc_file);

    //Bin Loader
    code = bin_code;

    //Virtual Machine
    ExecuteVM();

    return 0;
}
