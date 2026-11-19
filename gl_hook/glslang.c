#include <glslang.h>

void get_glslang_input(glslang_input_t *out)
{
    const PFNGLGETSTRINGPROC glGetString = get_proc_address("glGetString");

    int major = 1, minor = 0;
    const char *gl_version_str = (const char *)glGetString(GL_VERSION);
    const char *glsl_version_str = (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION);
    if (glsl_version_str)
        sscanf(glsl_version_str, "%d.%d", &major, &minor);

    bool is_gles = strstr(gl_version_str, "OpenGL ES");

    out->language = GLSLANG_SOURCE_GLSL;

    out->client = GLSLANG_CLIENT_OPENGL;
    out->client_version = GLSLANG_TARGET_OPENGL_450;

    out->target_language = GLSLANG_TARGET_NONE;
    out->target_language_version = GLSLANG_TARGET_SPV_1_0;

    out->default_version = major * 100 + minor;
    out->default_profile = GLSLANG_NO_PROFILE;
    if (is_gles)
        out->default_profile |= GLSLANG_ES_PROFILE;

    out->messages = GLSLANG_MSG_DEFAULT_BIT;
    out->resource = glslang_default_resource();
}
