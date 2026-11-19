#pragma once
#include "default.h"

typedef pvoid (*ilge_gl_hook_get_proc_address_f)(void *context, const char *name);

void ILGE_GL_HOOK_API ilge_init_gl_hook(ilge_gl_hook_get_proc_address_f get_proc_address_f, void *context);
void ILGE_GL_HOOK_API ilge_gl_hook_reset();

pvoid ILGE_GL_HOOK_API ilge_gl_hook_get_proc_address(const char *name);
