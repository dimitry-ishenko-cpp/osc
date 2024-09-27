cmake_minimum_required(VERSION 3.1)
project(libosc++ VERSION 1.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(HEADERS
    src/bundle.hpp
    src/dispatch.hpp
    src/element.hpp
    src/elements_0.hpp
    src/elements.hpp
    src/errors.hpp
    src/message.hpp
    src/packet.hpp
    src/types.hpp
    src/value.hpp
    src/values.hpp
)
set(OVERALL_HEADER src/osc++.hpp)

set(SOURCES
    src/bundle.cpp
    src/dispatch.cpp
    src/element.cpp
    src/message.cpp
    src/packet.cpp
    src/value.cpp
)

include(GNUInstallDirs)

########################
string(REGEX REPLACE "^lib" "" LIBRARY_NAME ${PROJECT_NAME})
set(PROJECT_NAME_DEV ${PROJECT_NAME}-dev)
set(CMAKE_INSTALL_DOCDIR_DEV ${CMAKE_INSTALL_DATAROOTDIR}/doc/${PROJECT_NAME_DEV})

# shared library
add_library(shared SHARED ${HEADERS} ${SOURCES})
set_target_properties(shared PROPERTIES OUTPUT_NAME ${LIBRARY_NAME})
set_target_properties(shared PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(shared PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

install(TARGETS shared DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT shared)
install(FILES LICENSE.md DESTINATION ${CMAKE_INSTALL_DOCDIR} COMPONENT shared)

# static dev library and headers
add_library(static STATIC ${HEADERS} ${SOURCES})
set_target_properties(static PROPERTIES OUTPUT_NAME ${LIBRARY_NAME})

install(TARGETS static DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT static)
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_NAME} COMPONENT static)
install(FILES ${OVERALL_HEADER} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT static)
install(FILES LICENSE.md README.md DESTINATION ${CMAKE_INSTALL_DOCDIR_DEV} COMPONENT static)
