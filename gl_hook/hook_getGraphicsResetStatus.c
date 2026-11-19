#include <gl_hook.h>

static PFNGLGETGRAPHICSRESETSTATUSPROC safe_glGetGraphicsResetStatus_callback = NULL;
static const char *glGetGraphicsResetStatus_procs[] = {
    "glGetGraphicsResetStatus",
    "glGetGraphicsResetStatusARB",
    "glGetGraphicsResetStatusKHR",
    "glGetGraphicsResetStatusEXT",
};

bool reset_glGetGraphicsResetStatus()
{
    safe_glGetGraphicsResetStatus_callback = get_first_proc_address_on_proc_table_fixed(glGetGraphicsResetStatus_procs);

    return true;
}

GLenum GLAPIENTRY safe_glGetGraphicsResetStatus()
{
    GLenum status = GL_NO_ERROR;
    if (safe_glGetGraphicsResetStatus_callback)
        status = safe_glGetGraphicsResetStatus_callback();

    return status;
}
