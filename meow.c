#include "header.h"
#include "instruction_set.h"
#include "MeowVM/vm.h"
#include "MeowASM/assembler.h"
#include "MeowBC/linker.h"

int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        printf("\nPlease Provide the required parameters!"); exit(1);
    }

    //Assembler
    // -s, -o, -a, -r, -w, -d
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
            initialize_linker();
            add_constant((Value) {.type=INT32, .i32=10});
            add_constant((Value) {.type=INT32, .i32=10});
            add_opcode(ADD);
            add_opcode(OUT);
            initiate_linking();
        }
        else if (!strcmp(argv[1], "-w")) {
            
        } else {
            printf("\nUnknown Tag Provided\n"); exit(1);
        }
        if (argc > 3 && !strcmp(argv[argc-1], "-d")) {
            printf("Debugger is on baby!");
        }
        fclose(bc_file);
    }

    //Virtual Machine
    InitializeVM();
    ExecuteVM(false, false);

    return 0;
}
