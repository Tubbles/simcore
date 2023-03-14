#pragma once

#include <functional>

using callback_t = std::function<void()>;

enum class schedule_phase_t {
    update,
    draw,
    num_phases,
};

auto register_schedule_callback(schedule_phase_t phase, const callback_t &callback) noexcept -> void;
auto run_schedule() noexcept -> void;
