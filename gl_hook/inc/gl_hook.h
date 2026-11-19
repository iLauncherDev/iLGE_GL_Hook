#pragma once
#include "utils.h"
#include "glslang.h"
#include <ilge_gl_hook/gl_hook.h>

typedef struct ilge_gl_hook ilge_gl_hook_t;

struct ilge_gl_hook
{
    GLint extension_list_len;
    char *extension_list;

    GLint extension_count;
    char **extension_array;

    ilge_gl_hook_get_proc_address_f get_proc_address_f;
    void *context;
};

extern ilge_gl_hook_t main_hook;

typedef struct
{
    char *name;
    bool (*reset_hook)();
    void *hook_proc;
    void *out_proc;
} ilge_gl_hook_entry_t;

#define _TO_STRING(x) #x
#define TO_STRING(x) _TO_STRING(x)
#define HOOK_ENTRY(proc_name) {.name = TO_STRING(proc_name), .reset_hook = reset_##proc_name, .hook_proc = safe_##proc_name}

