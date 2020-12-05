cmake_minimum_required(VERSION 3.1)
project(libosc++ VERSION 0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(HEADERS
    osc++/bundle.hpp
    osc++/message.hpp
    osc++/types.hpp
    osc++/value.hpp
    osc++.hpp
)
set(SOURCES
    bundle.cpp
    message.cpp
    types.cpp
    value.cpp
)

########################
include(GNUInstallDirs)

set(PROJECT_NAME_DEV ${PROJECT_NAME}-dev)
set(CMAKE_INSTALL_DOCDIR_DEV ${CMAKE_INSTALL_DATADIR}/doc/${PROJECT_NAME_DEV})

# shared library
add_library(shared SHARED ${HEADERS} ${SOURCES})
set_target_properties(shared PROPERTIES OUTPUT_NAME osc++)
set_target_properties(shared PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(shared PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

install(TARGETS shared DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT shared)
install(FILES LICENSE.md DESTINATION ${CMAKE_INSTALL_DOCDIR} COMPONENT shared)

# static dev library and headers
add_library(static STATIC ${HEADERS} ${SOURCES})
set_target_properties(static PROPERTIES OUTPUT_NAME osc++)

install(TARGETS static DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT static)
install(DIRECTORY osc++ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT static)
install(FILES osc++.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT static)
install(FILES LICENSE.md README.md DESTINATION ${CMAKE_INSTALL_DOCDIR_DEV} COMPONENT static)

########################
set(CPACK_STRIP_FILES ON)
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Library for generating and parsing OSC packets.")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Dimitry Ishenko <dimitry (dot) ishenko (at) (gee) mail (dot) com>")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_DEB_COMPONENT_INSTALL ON)

set(CPACK_DEBIAN_SHARED_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_DEBIAN_SHARED_PACKAGE_SHLIBDEPS ON)

set(CPACK_DEBIAN_STATIC_PACKAGE_NAME ${PROJECT_NAME_DEV})
set(CPACK_DEBIAN_STATIC_PACKAGE_DEPENDS ${CPACK_DEBIAN_SHARED_PACKAGE_NAME})

include(CPack)
cpack_add_component(shared)
cpack_add_component(static DESCRIPTION
    "This package contains headers and static libraries needed for development."
)
