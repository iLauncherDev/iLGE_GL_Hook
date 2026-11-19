#include <gl_hook.h>

static PFNGLSHADERSOURCEPROC safe_glShaderSource_callback = NULL;

static const char *proc_1 = "glShaderSource";

int __strnlen(const char *string, const int *length)
{
    int i = 0;
    while ((!length || (length && i < *length)) && string[i] != '\0')
        i++;

    return i;
}

bool reset_glShaderSource()
{
    safe_glShaderSource_callback = get_first_proc_address_on_proc_table(&proc_1, 1);

    return safe_glShaderSource_callback != NULL;
}

void GLAPIENTRY safe_glShaderSource(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length)
{
    if (!string || !count)
        return;

    GLchar *alloc_string = NULL;
    glslang_shader_t *glsl_shader = NULL;

    GLint required_length = 1, current_offset = 0;
    for (int i = 0; i < count; i++)
    {
        const GLchar *const *current_string = &string[i];
        const GLint *current_length = length ? &length[i] : NULL;

        if (*current_string)
            required_length += __strnlen(*current_string, current_length);
    }

    alloc_string = malloc(required_length);
    if (!alloc_string)
        goto result;
    *alloc_string = '\0';

    for (int i = 0; i < count; i++)
    {
        const GLchar *const *current_string = &string[i];
        const GLint *current_length = length ? &length[i] : NULL;
        if (!(*current_string))
            continue;

        int string_len = __strnlen(*current_string, current_length);
        memcpy(&alloc_string[current_offset], *current_string, string_len);

        current_offset += string_len;
        alloc_string[current_offset] = '\0';
    }

    glslang_input_t glsl_info = {0};
    get_glslang_input(&glsl_info);
    glsl_info.stage = GLSLANG_STAGE_VERTEX;
    glsl_info.code = alloc_string;

    glsl_shader = glslang_shader_create(&glsl_info);
    if (!glsl_shader)
        goto result;

    if (!glslang_shader_preprocess(glsl_shader, &glsl_info))
    {
        printf("ERROR While preprocessing glsl shader\n%s\n%s\n",
               glslang_shader_get_info_log(glsl_shader), glslang_shader_get_info_debug_log(glsl_shader));

        goto result;
    }

    const GLchar *string_list[] = {
        glslang_shader_get_preprocessed_code(glsl_shader),
    };

    if (safe_glShaderSource_callback)
        safe_glShaderSource_callback(shader, sizeof(string_list) / sizeof(*string_list), string_list, NULL);

result:
    if (glsl_shader)
        glslang_shader_delete(glsl_shader);

    if (alloc_string)
        free(alloc_string);
}
