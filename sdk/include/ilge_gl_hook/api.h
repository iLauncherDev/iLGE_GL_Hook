#pragma once

#if defined(_WIN32)
#define ILGE_DLL_EXPORT __declspec(dllexport)
#define ILGE_DLL_IMPORT __declspec(dllimport)
#define ILGE_API_CALL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define ILGE_DLL_EXPORT __attribute__((visibility("default")))
#define ILGE_DLL_IMPORT __attribute__((visibility("default")))
#define ILGE_API_CALL
#else
#error "Unknown compiler!"
#endif

#ifdef ILGE_GL_HOOK
#define ILGE_GL_HOOK_API ILGE_DLL_EXPORT ILGE_API_CALL
#else
#define ILGE_GL_HOOK_API ILGE_DLL_IMPORT ILGE_API_CALL
#endif
