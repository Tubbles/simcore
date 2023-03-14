#include "ecs.hpp"
#include "schedule.hpp"
#include "tick.hpp"
#include "types.hpp"
#include "vec3.hpp"

#include <fmt/core.h>
#include <thread>

using namespace std::chrono_literals;

// This is the best way to do it for a constexpr getter function
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
entt::registry g_registry;

static void setup() {
    auto &registry = get_registry();

    for (auto index = 0; index < 10; ++index) {
        const auto entity = registry.create();
        registry.emplace<position>(entity, vec3_t{index * 1., index * 1.});
        if (index % 2 == 0 || index % 3 == 0) {
            registry.emplace<velocity>(entity, vec3_t{index * .1, index * .1});
        }
    }
}

static void update() {
    auto &registry = get_registry();

    auto view = registry.view<const position, velocity>();

    view.each([](const auto &pos, auto &vel) {
        fmt::print("pos: {}, vel: {}\n", std::string{pos.vec}, std::string{vel.vec});
        vel.vec.x += 1.0;
        vel.vec.y += 2.0;
    });

    static std::chrono::time_point last_timepoint{tick::get_timestamp_now()};
    const auto now = tick::get_timestamp_now();
    const auto duration_since_last_update = std::chrono::duration_cast<f64>(now - last_timepoint);
    const auto estimated_ticks_per_second = 1 / duration_since_last_update.count();
    fmt::print("Estimated ticks per second: {}\n", estimated_ticks_per_second);
}

int main() {
    setup();
    tick::init();
    register_schedule_callback(schedule_phase_t::update, update);

    while (true) {
        fmt::print("Tick number {}\n", tick::get());
        run_schedule();
        constexpr const f64 ticks_per_second = 60.0;
        constexpr const f64 tick_period_us = 1000000.0 / ticks_per_second;
        auto now = tick::get_timestamp_now();
        const std::chrono::duration<f64, std::micro> tick_duration = now - tick::get_timestamp_start_of_tick();
        const auto remaining_time = std::chrono::duration<f64, std::micro>{tick_period_us} - tick_duration;
        std::this_thread::sleep_for(remaining_time);
    }
}
