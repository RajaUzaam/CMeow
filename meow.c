#include "vm.h"
#include "assembler.h"
#include "instruction_set.h"

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
    printf("Executing VM\n");
    ExecuteVM();

    return 0;
}
