#include "header.h"
#include "instruction_set.h"
#include "MeowVM/vm.h"
#include "MeowASM/assembler.h"

int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        printf("\nPlease Provide the required parameters!"); exit(1);
    }

    //Assembler
    // -s, -o, -a, -r, -w
    if (argc > 1) {
        FILE* bc_file = fopen(argv[2], "r");
        if (!strcmp(argv[1], "-s")) {

        }
        else if (!strcmp(argv[1], "-a")) {
            ExecuteAssembler(bc_file);
            code = bin_code;
            ConstructBin();
        }
        else if (!strcmp(argv[1], "-o")) {
            
        } 
        else if (!strcmp(argv[1], "-r")) {

        }
        else if (!strcmp(argv[1], "-w")) {
            
        } else {
            printf("\nUnknown Tag Provided\n"); exit(1);
        }
        fclose(bc_file);
    }

    //Bin Loader

    //Virtual Machine
    ExecuteVM();

    return 0;
}
