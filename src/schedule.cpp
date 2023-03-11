#include "schedule.hpp"

#include <map>
#include <vector>

static std::map<schedule_phase_t, std::vector<callback_t>> callbacks;

auto register_schedule_callback(schedule_phase_t phase, callback_t callback) noexcept -> void {
    if (!callbacks.contains(phase)) {
        callbacks.insert({phase, {}});
    }
    callbacks.at(phase).push_back(callback);
}

auto run_schedule() noexcept -> void {
    const schedule_phase_t phases[] = {schedule_phase_t::update, schedule_phase_t::draw};
    for (auto phase : phases) {
        if (!callbacks.contains(phase)) {
            callbacks.insert({phase, {}});
        }

        for (const auto &callback : callbacks.at(phase)) {
            callback();
        }
    }
}
