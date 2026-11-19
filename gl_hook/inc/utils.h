#pragma once
#include "default.h"

#define get_first_proc_address_on_proc_table_fixed(proc_list) get_first_proc_address_on_proc_table(proc_list, sizeof(proc_list) / sizeof(*proc_list))

pvoid get_proc_address(const char *name);
void *get_first_proc_address_on_proc_table(const char **proc_list, int proc_count);
