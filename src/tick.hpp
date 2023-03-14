#pragma once

#include "schedule.hpp"
#include "types.hpp"

namespace tick {
constexpr static auto &get_timestamp_now = std::chrono::system_clock::now;
auto init() noexcept -> void;
auto update() noexcept -> void;
auto get() noexcept -> u64;
auto get_timestamp_start_of_tick() noexcept -> std::chrono::time_point<std::chrono::system_clock>;
} // namespace tick
