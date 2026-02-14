project(simple_app_with_examples)

set(H_FILES
    CustomLogger.h
)

set(CPP_FILES
    CustomLogger.cpp
    main.cpp
)

add_executable(${PROJECT_NAME}
    ${CPP_FILES}
    ${H_FILES}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    SSLogWrapper::SSLogWrapper
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:APP_DEBUG>
)

if (NOT DEFINED CMAKE_DEBUG_POSTFIX)
    set(CMAKE_DEBUG_POSTFIX "d")
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
    OUTPUT_NAME ${CMAKE_PROJECT_NAME}
    INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib"
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

