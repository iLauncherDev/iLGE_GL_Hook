#include <gl_hook.h>

static PFNGLGETSTRINGPROC safe_glGetString_callback = NULL;

static const char *proc_1 = "glGetString";

bool reset_glGetString()
{
    safe_glGetString_callback = get_first_proc_address_on_proc_table(&proc_1, 1);

    return safe_glGetString_callback != NULL;
}

const_pchar GLAPIENTRY safe_glGetString(GLenum name)
{
    const_pchar out = NULL;

    switch (name)
    {
    case GL_EXTENSIONS:
        out = main_hook.extension_list;
        break;

    default:
        if (safe_glGetString_callback)
            out = (const_pchar)safe_glGetString_callback(name);

        break;
    }

    return out;
}
