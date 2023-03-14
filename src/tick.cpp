#include "tick.hpp"

namespace tick {
// This is the best way to do it for a constexpr getter function
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static u64 ticks_var;
// This is the best way to do it for a constexpr getter function
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static std::chrono::time_point<std::chrono::system_clock> timestamp_var;

auto init() noexcept -> void { register_schedule_callback(schedule_phase_t::pre_update, update); }
auto update() noexcept -> void {
    timestamp_var = get_timestamp_now();
    ticks_var += 1;
}

auto get() noexcept -> u64 { return ticks_var; }
auto get_timestamp_start_of_tick() noexcept -> std::chrono::time_point<std::chrono::system_clock> {
    return timestamp_var;
}
} // namespace tick
