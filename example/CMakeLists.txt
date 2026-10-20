# example

find_package(PkgConfig REQUIRED)
pkg_check_modules(asio REQUIRED IMPORTED_TARGET asio)
add_library(asio::asio ALIAS PkgConfig::asio)

add_executable(client client.cpp)
target_link_libraries(client osc++::osc++)

add_executable(server server.cpp)
target_link_libraries(server osc++::osc++)
