cmake_minimum_required(VERSION 3.0.2)

# Build Properties
set(CMAKE_INSTALL_INCLUDEDIR "include" CACHE PATH "Default relative include path.")
set(CMAKE_INSTALL_LIBDIR "lib" CACHE PATH "Default relative lib path.")

if(MSVC AND NOT "${FORCE_MSVC_RUNTIME}" STREQUAL "")
    message(STATUS "rpmalloc: Forcing msvc runtime to ${FORCE_MSVC_RUNTIME}")
    force_msvc_runtime()
endif()

# Targets
project(rpmalloc)
set(HEADERS rpmalloc/rpmalloc.h)
set(SOURCES rpmalloc/rpmalloc.c)
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")
target_include_directories(rpmalloc INTERFACE
  $<BUILD_INTERFACE:${rpmalloc_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)
include_directories(rpmalloc)
            
# Deployment
install ( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/rpmalloc/
          DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/rpmalloc
          FILES_MATCHING PATTERN "*.h")
install (TARGETS ${PROJECT_NAME}
         ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
         LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
