cmake_minimum_required(VERSION 3.0.2)

# Build Properties
set(CMAKE_INSTALL_INCLUDEDIR "include" CACHE PATH "Default relative include path.")
set(CMAKE_INSTALL_LIBDIR "lib" CACHE PATH "Default relative lib path.")

if(MSVC AND NOT "${FORCE_MSVC_RUNTIME}" STREQUAL "")
    message(STATUS "rpmalloc: Forcing msvc runtime to ${FORCE_MSVC_RUNTIME}")
    force_msvc_runtime()
endif()

# Source Files
set(HEADERS rpmalloc/rpmalloc.h)
set(SOURCES rpmalloc/rpmalloc.c)

# Targets
project(rpmalloc)

set(RPMALLOC_STATIC_LIBRARY ${PROJECT_NAME}_static)
set(RPMALLOC_SHARED_LIBRARY ${PROJECT_NAME})

add_library(${RPMALLOC_STATIC_LIBRARY} STATIC ${SOURCES})
set_target_properties(${RPMALLOC_STATIC_LIBRARY} PROPERTIES DEBUG_POSTFIX "d")
target_compile_definitions(${RPMALLOC_STATIC_LIBRARY} PUBLIC -DRPMALLOC_STATIC_LIB)
target_include_directories(${RPMALLOC_STATIC_LIBRARY} INTERFACE $<BUILD_INTERFACE:${rpmalloc_SOURCE_DIR}> $<INSTALL_INTERFACE:include>)

add_library(${RPMALLOC_SHARED_LIBRARY} SHARED ${SOURCES} ${HEADERS})
set_target_properties(${RPMALLOC_SHARED_LIBRARY} PROPERTIES DEBUG_POSTFIX "d")
target_compile_definitions(${RPMALLOC_SHARED_LIBRARY} PRIVATE -DRPMALLOC_EXPORTS_API)
target_include_directories(${RPMALLOC_SHARED_LIBRARY} INTERFACE $<BUILD_INTERFACE:${rpmalloc_SOURCE_DIR}> $<INSTALL_INTERFACE:include>)

include_directories(rpmalloc)

# Deployment
install ( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/rpmalloc/
          DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/rpmalloc
          FILES_MATCHING PATTERN "*.h")
install (TARGETS ${RPMALLOC_STATIC_LIBRARY} ${RPMALLOC_SHARED_LIBRARY}
         RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
         ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
         LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
