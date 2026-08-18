find_package(spdlog QUIET)
option(ENABLE_SPDLOG "Enable 3rd-party logger 'spdlog`" ON)
option(ENABLE_ANDROID "Enable android logger" ON)

project(logger
    VERSION 0.0.1
    LANGUAGES CXX
)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


set(CPP_FILES
    ILogger.cpp
)

if(${ENABLE_SPDLOG})
    set(H_FILES "${H_FILES};spdlogWrapper/SpdLogWrapper.h")
    set(CPP_FILES "${CPP_FILES};spdlogWrapper/SpdLogWrapper.cpp")
elseif(${ENABLE_ANDROID})
    set(H_FILES "${H_FILES};androidLogger/AndroidLogger.h")
    set(CPP_FILES "${CPP_FILES};androidLogger/AndroidLogger.cpp")

    find_library(
      log-lib
      log
    )

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
        $<$<BOOL:${ENABLE_ANDROID}>:${log-lib}>
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE $<$<BOOL:${ENABLE_SPDLOG}>:SPD_ENABLED>
    PUBLIC $<$<BOOL:${BUILD_SHARED_LIBS}>:SSLOGWRAPPER_DLL>
    PRIVATE $<$<BOOL:${BUILD_SHARED_LIBS}>:SSLOGWRAPPER_DLL_EXPORTS>
    INTERFACE $<$<BOOL:${BUILD_SHARED_LIBS}>:SSLOGWRAPPER_DLL_IMPORTS>
)


##
## Installation
##

install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME}" DESTINATION include)

GenerateLibraryConfig(${CMAKE_PROJECT_NAME} "")

