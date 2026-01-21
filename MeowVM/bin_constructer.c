// #include "vm.h"

// static uint16_t read_int16(uint8_t *code, int64_t offset) {
//     uint16_t val;
//     memcpy(&val, &code[offset], sizeof(uint16_t));
//     return val;
// }

// static uint32_t read_int32(uint8_t *code, int64_t offset) {
//     uint32_t val;
//     memcpy(&val, &code[offset], sizeof(uint32_t));
//     return val;
// }

// static uint64_t read_int64(uint8_t *code, int64_t offset) {
//     uint64_t val;
//     memcpy(&val, &code[offset], sizeof(uint64_t));
//     return val;
// }

// // Construct constants table
// void construct_const_table(uint64_t addr) {
//     co_consts_size = read_int32(code, addr);
//     co_consts = realloc(co_consts, sizeof(Value) * co_consts_size);

//     uint64_t i = addr + 4; // skip table size
//     for (uint64_t idx = 0; idx < co_consts_size; idx++) {
//         co_consts[idx].type = code[i++]; // type byte
//         int64_t new_val;
//         memcpy(&new_val, &code[i], GetBytes(co_consts[idx].type));
//         switch (co_consts[idx].type) {
//             case INT32:
//                 memcpy(&co_consts[idx].i32, &new_val, GetBytes(co_consts[idx].type)); break;
//             case INT64:
//                 memcpy(&co_consts[idx].i64, &new_val, GetBytes(co_consts[idx].type)); break;
//             case BOOL:
//                 memcpy(&co_consts[idx].bl, &new_val, GetBytes(co_consts[idx].type)); break;
//             case CHAR:
//                 memcpy(&co_consts[idx].chr, &new_val, GetBytes(co_consts[idx].type)); break;
//             case REAL32:
//                 memcpy(&co_consts[idx].r32, &new_val, GetBytes(co_consts[idx].type)); break;
//             case REAL64:
//                 memcpy(&co_consts[idx].r64, &new_val, GetBytes(co_consts[idx].type)); break;
//             default:
//                 perror("Unknown Const Type!");
//                 exit(1);
//         }
//         i += GetBytes(co_consts[idx].type);
//     }
// }

// // Construct globals table
// void construct_global_table(uint64_t addr) {
//     globals_size = read_int32(code, addr);
//     globals = realloc(globals, sizeof(Value) * globals_size);

//     uint64_t i = addr + 4; // skip table size
//     for (uint64_t idx = 0; idx < globals_size; idx++) {
//         globals[idx].type = code[i++];
//         switch (globals[idx].type) {
//             case INT32: globals[idx].i32 = 0; break;
//             case INT64: globals[idx].i64 = 0; break;
//             case BOOL: globals[idx].bl = 0; break;
//             case CHAR: globals[idx].chr = 0; break;
//             case REAL32: globals[idx].r32 = 0; break;
//             case REAL64: globals[idx].r64 = 0; break;
//             default:
//                 perror("Unknown Global Type!");
//                 exit(1);
//         }
//     }
// }

// // Load function bytecode
// void load_func_bytecode(uint64_t idx, uint64_t addr, uint8_t **bc_code, uint64_t size) {
//     vm.functions[idx]->code_size = size;
//     *bc_code = malloc(sizeof(uint8_t) * size);
//     memcpy(*bc_code, &code[addr], size);
// }

// // Construct functions table
// void construct_func_table(uint64_t addr, uint64_t func_count) {
//     uint64_t ip = addr;

//     for (uint64_t j = 0; j < func_count; j++) {
//         int32_t read_opcodes = 0;
//         bool entry = false;
//         if (code[ip] == 0xFF) {
//             ip++;
//             entry = true;
//         }
//         uint64_t idx = 0;
//         uint64_t offset = 0;
//         uint64_t code_size = 0;
//         uint64_t opcode_num = (entry) ? (3) : (5);
//         while (read_opcodes < opcode_num) {
//             uint8_t tag = code[ip++];
//             switch(tag) {
//                 case INDEX:
//                     idx = read_int32(code, ip);
//                     read_opcodes++; ip += 4;
//                     vm.functions[j]->idx = idx;
//                     if (entry) {
//                         vm.call_stack = malloc(sizeof(Frame));
//                         vm.call_stack[0].func_ptr = vm.functions[func_count-1];
//                         vm.call_stack[0].ip = 0;
//                         vm.call_stack[0].ret_addr = 0;
//                     }
//                     break;
//                 case CODE_OFFSET:
//                     offset = read_int64(code, ip);
//                     ip += 8; read_opcodes++;
//                     break;
//                 case CODE_SIZE:
//                     code_size = read_int32(code, ip);
//                     ip += 4; read_opcodes++;
//                     load_func_bytecode(idx, offset, &vm.functions[idx]->code, code_size);
//                     break;
//                 case ARGS: {
//                     uint64_t arg_num = read_int16(code, ip);
//                     ip += sizeof(int16_t); read_opcodes++;
//                     vm.functions[idx]->arg_num = arg_num;
//                     vm.functions[idx]->args = malloc(sizeof(ValueType) * arg_num);
//                     for (uint64_t j = 0; j < arg_num; j++) {
//                         vm.functions[idx]->args[j] = code[ip++];
//                     }
//                     break;
//                 }
//                 case LOCALS: {
//                     uint64_t local_num = read_int16(code, ip);
//                     ip += sizeof(int16_t); read_opcodes++;
//                     vm.functions[idx]->local_num = local_num;
//                     vm.functions[idx]->locals = malloc(sizeof(ValueType) * local_num);
//                     for (uint64_t j = 0; j < local_num; j++) {
//                         vm.functions[idx]->locals[j] = code[ip++];
//                     }
//                     break;
//                 }

//                 default:
//                     printf("{%d}", tag);
//                     perror("Unknown function tag!");
//                     exit(1);

//             }
//         }
//     }
// }

// // Construct frame table
// void construct_frame_table(int64_t addr) {
//     uint64_t func_count = read_int32(code, addr);
//     vm.func_count = func_count;
//     vm.functions = malloc(sizeof(Function*) * func_count);
//     for (uint64_t i = 0; i < func_count; i++) {
//         vm.functions[i] = malloc(sizeof(Function));
//         vm.functions[i]->code = NULL;
//         vm.functions[i]->args = NULL;
//         vm.functions[i]->locals = NULL;
//     }
//     construct_func_table(addr + 4, func_count);
// }

// // Construct full binary
// void ConstructBin() {
//     uint64_t header_size = read_int32(code, 0);

//     int64_t i = 4;
    
//     while (i < header_size) {
//         switch (code[i++]) {
//             case CONSTANTS_TABLE: {
//                 uint64_t table_addr = read_int64(code, i);
//                 i += 8;
//                 construct_const_table(table_addr);
//                 break;
//             }

//             case GLOBALS_TABLE: {
//                 uint64_t table_addr = read_int64(code, i);
//                 i += 8;
//                 construct_global_table(table_addr);
//                 break;
//             }

//             case FUNCTIONS_TABLE: {
//                 uint64_t table_addr = read_int64(code, i);
//                 i += 16;
//                 construct_frame_table(table_addr);
//                 break;
//             }

//             default:
//                 perror("Unknown Table in header!");
//                 exit(1);
//         }
//     }
// }