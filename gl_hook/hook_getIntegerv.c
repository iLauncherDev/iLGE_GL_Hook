#include <gl_hook.h>

static PFNGLGETINTEGERVPROC safe_glGetIntegerv_callback = NULL;

static const char *proc_1 = "glGetIntegerv";

bool reset_glGetIntegerv()
{
    safe_glGetIntegerv_callback = get_first_proc_address_on_proc_table(&proc_1, 1);

    return safe_glGetIntegerv_callback != NULL;
}

void GLAPIENTRY safe_glGetIntegerv(GLenum pname, GLint *data)
{
    switch (pname)
    {
    case GL_NUM_EXTENSIONS:
        *data = main_hook.extension_count;
        break;

    default:
        if (safe_glGetIntegerv_callback)
            safe_glGetIntegerv_callback(pname, data);

        break;
    }
}
