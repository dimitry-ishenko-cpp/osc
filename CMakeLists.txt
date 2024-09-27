cmake_minimum_required(VERSION 3.16) # focal
project(libosc++ VERSION 1.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
string(REGEX REPLACE "^lib" "" LIBRARY_NAME ${PROJECT_NAME})

add_library(shared SHARED ${HEADERS} ${SOURCES})
set_target_properties(shared PROPERTIES
    OUTPUT_NAME ${LIBRARY_NAME}
    VERSION     ${PROJECT_VERSION}
    SOVERSION   ${PROJECT_VERSION_MAJOR}
)

add_library(static STATIC ${HEADERS} ${SOURCES})
set_target_properties(static PROPERTIES
    OUTPUT_NAME ${LIBRARY_NAME}
)

install(TARGETS shared static DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_NAME})
install(FILES ${OVERALL_HEADER} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES LICENSE.md README.md DESTINATION ${CMAKE_INSTALL_DOCDIR})
