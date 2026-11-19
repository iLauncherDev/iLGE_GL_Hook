#include <gl_hook.h>

static PFNGLVERTEXATTRIBDIVISORPROC safe_glVertexAttribDivisor_callback;
static const char *glVertexAttribDivisor_procs[] = {
    "glVertexAttribDivisor",
    "glVertexAttribDivisorARB",
    "glVertexAttribDivisorEXT",
    "glVertexAttribDivisorANGLE",
};

static PFNGLDRAWELEMENTSINSTANCEDPROC safe_glDrawElementsInstanced_callback;
static const char *glDrawElementsInstanced_procs[] = {
    "glDrawElementsInstanced",
    "glDrawElementsInstancedARB",
    "glDrawElementsInstancedEXT",
    "glDrawElementsInstancedANGLE",
};

static PFNGLDRAWARRAYSINSTANCEDPROC safe_glDrawArraysInstanced_callback;
static const char *glDrawArraysInstanced_procs[] = {
    "glDrawArraysInstanced",
    "glDrawArraysInstancedARB",
    "glDrawArraysInstancedEXT",
    "glDrawArraysInstancedANGLE",
};

bool reset_glVertexAttribDivisor()
{
    safe_glVertexAttribDivisor_callback = get_first_proc_address_on_proc_table_fixed(glVertexAttribDivisor_procs);

    return safe_glVertexAttribDivisor_callback != NULL;
}

void GLAPIENTRY safe_glVertexAttribDivisor(GLuint index, GLuint divisor)
{
    safe_glVertexAttribDivisor_callback(index, divisor);
}

bool reset_glDrawElementsInstanced()
{
    safe_glDrawElementsInstanced_callback = get_first_proc_address_on_proc_table_fixed(glDrawElementsInstanced_procs);

    return safe_glDrawElementsInstanced_callback != NULL;
}

void GLAPIENTRY safe_glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount)
{
    safe_glDrawElementsInstanced_callback(mode, count, type, indices, instancecount);
}

bool reset_glDrawArraysInstanced()
{
    safe_glDrawArraysInstanced_callback = get_first_proc_address_on_proc_table_fixed(glDrawArraysInstanced_procs);

    return safe_glDrawArraysInstanced_callback != NULL;
}

void GLAPIENTRY safe_glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount)
{
    safe_glDrawArraysInstanced_callback(mode, first, count, instancecount);
}
