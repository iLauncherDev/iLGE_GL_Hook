#include <gl_hook.h>

static void GLAPIENTRY (*safe_glDepthRangef64)(GLclampd n, GLclampd f) = NULL;
static void GLAPIENTRY (*safe_glDepthRangef32)(GLfloat n, GLfloat f) = NULL;

static const char *proc_1 = "glDepthRange";
static const char *proc_2 = "glDepthRangef";

bool reset_glDepthRangef()
{
    safe_glDepthRangef64 = (void *)get_first_proc_address_on_proc_table(&proc_1, 1);
    safe_glDepthRangef32 = (void *)get_first_proc_address_on_proc_table(&proc_2, 1);

    return safe_glDepthRangef64 != NULL || safe_glDepthRangef32 != NULL;
}

void GLAPIENTRY safe_glDepthRangef(GLfloat n, GLfloat f)
{
    if (safe_glDepthRangef64)
        safe_glDepthRangef64(n, f);
    else if (safe_glDepthRangef32)
        safe_glDepthRangef32(n, f);
}
