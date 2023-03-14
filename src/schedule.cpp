#include "schedule.hpp"

#include <map>
#include <vector>

// I'd argue it's not really global..
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static std::map<schedule_phase_t, std::vector<callback_t>> callbacks;

auto register_schedule_callback(schedule_phase_t phase, const callback_t &callback) noexcept -> void {
    if (!callbacks.contains(phase)) {
        callbacks.insert({phase, {}});
    }
    callbacks.at(phase).push_back(callback);
}

auto run_schedule() noexcept -> void {
    for (size_t phase_index = 0; phase_index < static_cast<size_t>(schedule_phase_t::num_phases); ++phase_index) {
        auto phase = static_cast<schedule_phase_t>(phase_index);

        if (!callbacks.contains(phase)) {
            callbacks.insert({phase, {}});
        }

        for (const auto &callback : callbacks.at(phase)) {
            callback();
        }
    }
}
