#pragma once

#include "types.hpp"

#include <fmt/core.h>

#define ARR_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

#define CRASH(message) crash(message, __FILE__, __LINE__)

[[noreturn]] inline auto crash(const std::string_view message, const std::string_view file, const int line) noexcept
    -> void {
    fmt::print(stderr, "CRASH: \"{}\" @ {}:{}\n", message, file, line);
    fflush(stderr);
    exit(1);
}

[[nodiscard]] inline auto clamp(double min, double x, double max) -> double {
    if (x < min) {
        return min;
    }
    if (x > max) {
        return max;
    }
    return x;
}

[[nodiscard]] inline auto lerp(double start, double end, double t) -> double { return (1.0 - t) * start + t * end; }
