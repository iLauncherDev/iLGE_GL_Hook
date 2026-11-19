#include <gl_hook.h>

bool reset_glClearDepthf();
void GLAPIENTRY safe_glClearDepthf(GLfloat d);

bool reset_glDepthRangef();
void GLAPIENTRY safe_glDepthRangef(GLfloat n, GLfloat f);

bool reset_glGetGraphicsResetStatus();
GLenum GLAPIENTRY safe_glGetGraphicsResetStatus();

bool reset_glGetIntegerv();
void GLAPIENTRY safe_glGetIntegerv(GLenum pname, GLint *data);

bool reset_glGetString();
const_pchar GLAPIENTRY safe_glGetString(GLenum name);

bool reset_glGetStringi();
const_pchar GLAPIENTRY safe_glGetStringi(GLenum name, GLuint index);

bool reset_glVertexAttribDivisor();
void GLAPIENTRY safe_glVertexAttribDivisor(GLuint index, GLuint divisor);

bool reset_glDrawElementsInstanced();
void GLAPIENTRY safe_glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount);

bool reset_glDrawArraysInstanced();
void GLAPIENTRY safe_glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);

bool reset_glShaderSource();
void GLAPIENTRY safe_glShaderSource(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length);

bool is_glslang_initialized = false;

ilge_gl_hook_t main_hook = {0};
ilge_gl_hook_entry_t hook_list[] = {
    HOOK_ENTRY(glClearDepthf),
    HOOK_ENTRY(glDepthRangef),

    HOOK_ENTRY(glGetGraphicsResetStatus),

    HOOK_ENTRY(glGetIntegerv),

    HOOK_ENTRY(glGetString),
    HOOK_ENTRY(glGetStringi),

    HOOK_ENTRY(glVertexAttribDivisor),
    HOOK_ENTRY(glDrawElementsInstanced),
    HOOK_ENTRY(glDrawArraysInstanced),

    HOOK_ENTRY(glShaderSource),
};

void ilge_init_glslang()
{
    if (is_glslang_initialized)
        return;

    glslang_initialize_process();
    is_glslang_initialized = true;
}

void ilge_uninit_glslang()
{
    if (!is_glslang_initialized)
        return;

    glslang_finalize_process();
    is_glslang_initialized = false;
}

void ILGE_GL_HOOK_API ilge_init_gl_hook(ilge_gl_hook_get_proc_address_f get_proc_address_f, void *context)
{
    main_hook.get_proc_address_f = get_proc_address_f;
    main_hook.context = context;

    ilge_gl_hook_reset();
}

void gl_hook_free_extensions()
{
    if (main_hook.extension_list)
        free(main_hook.extension_list);

    if (main_hook.extension_array)
    {
        for (int i = 0; i < main_hook.extension_count; i++)
        {
            void *ptr = main_hook.extension_array[i];
            if (ptr)
                free(ptr);
        }

        free(main_hook.extension_array);
    }

    main_hook.extension_count = 0;
    main_hook.extension_list = NULL;
    main_hook.extension_array = NULL;
}

void gl_hook_init_extensions(bool speculative_mode)
{
    PFNGLGETSTRINGPROC glGetString = get_proc_address("glGetString");

    PFNGLGETSTRINGIPROC glGetStringi = get_proc_address("glGetStringi");
    PFNGLGETINTEGERVPROC glGetIntegerv = get_proc_address("glGetIntegerv");

    ILGE_ASSERT(glGetString != NULL);
    ILGE_ASSERT(glGetStringi != NULL);
    ILGE_ASSERT(glGetIntegerv != NULL);

    if (speculative_mode)
    {
        main_hook.extension_list_len = 0;
        main_hook.extension_count = 0;
    }
    else
    {
        main_hook.extension_list = malloc(main_hook.extension_list_len + 1);
        ILGE_ASSERT(main_hook.extension_list != NULL);

        main_hook.extension_array = malloc(sizeof(*main_hook.extension_array) * main_hook.extension_count);
        ILGE_ASSERT(main_hook.extension_array != NULL);
    }

    const char *extension_list = (const char *)glGetString(GL_EXTENSIONS);

    if (extension_list)
    {
        if (speculative_mode)
            main_hook.extension_list_len = strlen(extension_list);
        else
            memcpy(main_hook.extension_list, extension_list, main_hook.extension_list_len + 1);

        int ext_index = 0;
        int start_offset = 0, current_offset = start_offset;

        while (true)
        {
            char chr1 = extension_list[current_offset];
            bool is_null_terminator = chr1 == '\0';

            if (is_null_terminator || chr1 == ' ')
            {
                int string_size = current_offset - start_offset;

                if (string_size > 0)
                {
                    if (!speculative_mode)
                    {
                        char *new_extension = malloc(string_size + 1);
                        if (new_extension)
                        {
                            memcpy(new_extension, &extension_list[start_offset], string_size);
                            new_extension[string_size] = '\0';
                        }

                        main_hook.extension_array[ext_index] = new_extension;
                    }

                    ext_index++;
                }

                start_offset = current_offset + 1;
            }

            if (is_null_terminator)
                break;
            current_offset++;
        }

        if (speculative_mode)
            main_hook.extension_count = ext_index;
    }
    else
    {
        int current_offset = 0;

        glGetIntegerv(GL_NUM_EXTENSIONS, &main_hook.extension_count);

        for (int i = 0; i < main_hook.extension_count; i++)
        {
            const bool is_end_of_list = (i + 1) >= main_hook.extension_count;

            const char *extension = (const char *)glGetStringi(GL_EXTENSIONS, i);
            const int extension_len = strlen(extension);

            if (!speculative_mode)
            {
                char *string_window = &main_hook.extension_list[current_offset];
                string_window[extension_len] = is_end_of_list ? '\0' : ' ';
                memcpy(string_window, extension, extension_len);

                char *new_extension = malloc(extension_len + 1);
                if (new_extension)
                    memcpy(new_extension, extension, extension_len + 1);

                main_hook.extension_array[i] = new_extension;
            }
            else
            {
                if (!is_end_of_list)
                    main_hook.extension_list_len += 1;

                main_hook.extension_list_len += extension_len;
            }

            current_offset += extension_len + 1;
        }
    }
}

void ILGE_GL_HOOK_API ilge_gl_hook_reset()
{
    ilge_uninit_glslang();
    ilge_init_glslang();

    gl_hook_free_extensions();
    gl_hook_init_extensions(true);
    gl_hook_init_extensions(false);

    for (size_t i = 0; i < sizeof(hook_list) / sizeof(*hook_list); i++)
    {
        ilge_gl_hook_entry_t *entry = &hook_list[i];

        entry->out_proc = entry->reset_hook() ? entry->hook_proc : NULL;

        // printf("entry->name = '%s'\n", entry->name);
        // printf("entry->out_proc = %p\n", entry->out_proc);
    }
}

pvoid ILGE_GL_HOOK_API ilge_gl_hook_get_proc_address(const char *name)
{
    for (size_t i = 0; i < sizeof(hook_list) / sizeof(*hook_list); i++)
    {
        ilge_gl_hook_entry_t *entry = &hook_list[i];
        if (!strcmp(entry->name, name))
            return entry->out_proc;
    }

    return get_proc_address(name);
}
