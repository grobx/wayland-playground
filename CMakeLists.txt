cmake_minimum_required(VERSION 3.5)

project(wl-barman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

subdirs(protocols EXCLUDE_FROM_ALL)

add_executable(wl-barman src/main.cpp)
target_link_libraries(wl-barman wl-barman-protocols)

include(FindPkgConfig)
pkg_check_modules(WAYLANDPP_CLIENT          wayland-client++            REQUIRED IMPORTED_TARGET)
pkg_check_modules(WAYLANDPP_CLIENT_EXTRA    wayland-client-extra++      REQUIRED IMPORTED_TARGET)

target_link_libraries(wl-barman PkgConfig::WAYLANDPP_CLIENT)
target_link_libraries(wl-barman PkgConfig::WAYLANDPP_CLIENT_EXTRA)

include(GNUInstallDirs)
install(TARGETS wl-barman
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
