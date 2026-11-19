#pragma once
#define ILGE_GL_HOOK
#include <ilge_gl_hook/default.h>
#include "glad/gles2.h"

#define memclr(d, s) memset(d, 0, s)

#define ILGE_ASSERT(cond)                                          \
    if (!(cond))                                                   \
    {                                                              \
        fprintf(stderr, "ASSERT FAILED: %s\nFile: %s\nLine: %d\n", \
                #cond, __FILE__, __LINE__);                        \
        abort();                                                   \
    }
