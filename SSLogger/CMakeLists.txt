find_package(spdlog QUIET)
option(ENABLE_SPDLOG "Enable 3rd-party logger 'spdlog`" ON)

project(logger)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


set(CPP_FILES
    ILogger.cpp
)

if(${ENABLE_SPDLOG})
    set(H_FILES "${H_FILES};spdlogWrapper/SpdLogWrapper.h")
    set(CPP_FILES "${CPP_FILES};spdlogWrapper/SpdLogWrapper.cpp")
else()
    set(H_FILES "${H_FILES};coutLogger/CoutLogger.h")
    set(CPP_FILES "${CPP_FILES};coutLogger/CoutLogger.cpp")
endif()


add_library(${PROJECT_NAME}
        ${H_FILES}
        ${CPP_FILES}
)
add_library(${CMAKE_PROJECT_NAME}::${CMAKE_PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        $<$<BOOL:${ENABLE_SPDLOG}>:spdlog::spdlog>
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<BOOL:${ENABLE_SPDLOG}>:SPD_ENABLED>
)

##
## Installation
##

install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME}" DESTINATION include)


install(TARGETS ${PROJECT_NAME}
        DESTINATION lib64
        EXPORT ${PROJECT_NAME}_targets
)

install(EXPORT ${PROJECT_NAME}_targets
        DESTINATION lib/cmake/${PROJECT_NAME}
        NAMESPACE ${CMAKE_PROJECT_NAME}::
)

