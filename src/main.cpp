#include <iostream>
#include <wayland-client.hpp>
#include <wayland-client-protocol-extra.hpp>
#include <wayland-client-protocol-unstable.hpp>
#include <wlr-layer-shell.hpp>

using namespace std;

int main()
{
    cout << "Hello, Wayland! [version " << WAYLAND_VERSION << "+" << WAYLANDPP_VERSION << "]" << endl;

    // connect to wayland and bind relevant objects
    wayland::display_t display;
    wayland::registry_t registry;
    wayland::compositor_t compositor;
    std::vector<wayland::output_t> outputs;
    wayland::seat_t seat;
    wayland::zwlr_layer_shell_v1_t layer_shell;
    registry = display.get_registry();
    registry.on_global() = [&](uint32_t name, std::string interface, uint32_t version) {
        if (interface == wayland::compositor_t::interface_name)
            registry.bind(name, compositor, version);
        else if (interface == wayland::output_t::interface_name)
        {
            auto& output = outputs.emplace_back();
            registry.bind(name, output, version);
        }
        else if (interface == wayland::seat_t::interface_name)
            registry.bind(name, seat, version);
        else if (interface == wayland::zwlr_layer_shell_v1_t::interface_name)
            registry.bind(name, layer_shell, version);
    };
    display.roundtrip();

    // enumerate outputs
    cout << "Outputs:\n";
    for (const auto& output : outputs) {
        cout << " '- " << output.get_class() << "@" << output.get_id() << "v" << output.get_version() << "\n";
    }

    return 0;
}
