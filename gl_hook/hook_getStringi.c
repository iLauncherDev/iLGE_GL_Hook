#include <gl_hook.h>

static PFNGLGETSTRINGIPROC safe_glGetStringi_callback = NULL;

static const char *proc_1 = "glGetStringi";

bool reset_glGetStringi()
{
    safe_glGetStringi_callback = get_first_proc_address_on_proc_table(&proc_1, 1);

    return safe_glGetStringi_callback != NULL;
}

const_pchar GLAPIENTRY safe_glGetStringi(GLenum name, GLuint index)
{
    const_pchar out = NULL;

    switch (name)
    {
    case GL_EXTENSIONS:
        if (main_hook.extension_array && index < main_hook.extension_count)
            out = main_hook.extension_array[index];

        break;

    default:
        if (safe_glGetStringi_callback)
            out = (const_pchar)safe_glGetStringi_callback(name, index);

        break;
    }

    return out;
}
