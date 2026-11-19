set(ILGE_LIB_NAME ilge_gl_hook)
set(ILGE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
set(ILGE_INCLUDE_PATH "${ILGE_PATH}/inc")

list(APPEND ILGE_SOURCE
    ${ILGE_PATH}/utils.c
    ${ILGE_PATH}/main.c

    ${ILGE_PATH}/glslang.c

    ${ILGE_PATH}/hook_clearDepthf.c
    ${ILGE_PATH}/hook_depthRangef.c

    ${ILGE_PATH}/hook_getGraphicsResetStatus.c

    ${ILGE_PATH}/hook_getIntegerv.c
    ${ILGE_PATH}/hook_getString.c
    ${ILGE_PATH}/hook_getStringi.c

    ${ILGE_PATH}/hook_instancing.c

    ${ILGE_PATH}/hook_shaderSource.c
)

add_library(${ILGE_LIB_NAME} SHARED ${ILGE_SOURCE})
set_target_properties(${ILGE_LIB_NAME} PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    C_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)

target_include_directories(${ILGE_LIB_NAME} PRIVATE ${ILGE_INCLUDE_PATH})
target_include_directories(${ILGE_LIB_NAME} PUBLIC ${ILGE_SDK_INCLUDE_PATH})
target_link_libraries(${ILGE_LIB_NAME} PRIVATE glslang glslang-default-resource-limits)
