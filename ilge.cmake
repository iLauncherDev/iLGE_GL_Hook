set(ILGE_SDK_INCLUDE_PATH "${CMAKE_CURRENT_LIST_DIR}/sdk/include")

include(FetchContent)

FetchContent_Declare(
    GLSLang
    GIT_REPOSITORY https://github.com/iLauncherDev/glslang.git
    GIT_TAG        ilge_token_pasting_hack
    GIT_REMOTE_UPDATE_STRATEGY CHECKOUT
)

block()
    set(GLSLANG_TESTS OFF CACHE BOOL "" FORCE)
    set(GLSLANG_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
    set(ENABLE_GLSLANG_BINARIES OFF CACHE BOOL "" FORCE)
    set(ENABLE_SPIRV OFF CACHE BOOL "" FORCE)
    set(ENABLE_HLSL OFF CACHE BOOL "" FORCE)
    set(ENABLE_CTEST OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(GLSLang)
endblock()

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/gl_hook)
