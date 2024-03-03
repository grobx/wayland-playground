# TODO: generate protocols
# wayland-scanner++ -x wayland-client-protocol-extra.hpp wlroots/protocol/wlr-layer-shell-unstable-v1.xml include/wlr-layer-shell.hpp src/wlr-layer-shell.cpp
add_library(wl-barman-protocols src/wlr-layer-shell.cpp)
target_include_directories(wl-barman-protocols PUBLIC include/)
