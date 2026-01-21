#ifndef EXE
#define EXE

#include "../header.h"
#include "type_handler.h"
#include "vm_instance.h"
#include "operations.h"
#include "globals.h"
#include "stack.h"

extern struct VM vm;

bool stop   (uint64_t operand);
bool push   (uint64_t operand);
bool dup    (uint64_t operand);
bool swap   (uint64_t operand);
bool out    (uint64_t operand);
bool store  (uint64_t operand);
bool load   (uint64_t operand);
bool add    (uint64_t operand);
bool sub    (uint64_t operand);
bool mul    (uint64_t operand);
bool div_   (uint64_t operand);
bool leave  (uint64_t operand);
bool enter  (uint64_t operand);
bool call   (uint64_t operand);
bool ret    (uint64_t operand);
bool load_a (uint64_t operand);
bool load_l (uint64_t operand);
bool store_l(uint64_t operand);
bool jmp    (uint64_t operand);
bool e_size (uint64_t operand);
bool ceq    (uint64_t operand);
bool cgt    (uint64_t operand);
bool clt    (uint64_t operand);
bool cgte   (uint64_t operand);
bool clte   (uint64_t operand);
bool cne    (uint64_t operand);
bool jpt    (uint64_t operand);
bool jpf    (uint64_t operand);
bool f_and  (uint64_t operand);
bool f_or   (uint64_t operand);
bool f_not  (uint64_t operand);
bool fb_ls  (uint64_t operand);
bool fb_rs  (uint64_t operand);
bool fb_and (uint64_t operand);
bool fb_or  (uint64_t operand);
bool fb_xor (uint64_t operand);
bool fb_not (uint64_t operand);

#endif