#include <fmt/core.h>
#include <vector>

auto main(int argc, char *argv[]) -> int {
    // cppcheck-suppress unreadVariable; args unused for now
    const std::vector<std::string> args(argv + 1, argv + argc);

    fmt::print("Hello, world!\n");
    return 0;
}
