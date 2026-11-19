#include <gl_hook.h>

static void GLAPIENTRY (*safe_glClearDepthf64)(GLdouble d) = NULL;
static void GLAPIENTRY (*safe_glClearDepthf32)(GLfloat d) = NULL;

static const char *proc_1 = "glClearDepth";
static const char *proc_2 = "glClearDepthf";

bool reset_glClearDepthf()
{
    safe_glClearDepthf64 = (void *)get_first_proc_address_on_proc_table(&proc_1, 1);
    safe_glClearDepthf32 = (void *)get_first_proc_address_on_proc_table(&proc_2, 1);

    return safe_glClearDepthf64 != NULL || safe_glClearDepthf32 != NULL;
}

void GLAPIENTRY safe_glClearDepthf(GLfloat d)
{
    if (safe_glClearDepthf64)
        safe_glClearDepthf64(d);
    else if (safe_glClearDepthf32)
        safe_glClearDepthf32(d);
}
