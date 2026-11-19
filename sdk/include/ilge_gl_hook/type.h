#pragma once

// Workaround for MSVC declaration parsing issue when using ILGE_GL_HOOK_API with pointer return types

#define ILGE_TYPEDEF(type_t, type) \
    typedef const type_t const_##type; \
    typedef type_t type

ILGE_TYPEDEF(void *, pvoid);
ILGE_TYPEDEF(char *, pchar);
