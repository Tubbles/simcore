#include "ecs.hpp"
#include "schedule.hpp"
#include "types.hpp"
#include "vec3.hpp"

#include <fmt/core.h>

entt::registry g_registry;

static void update() {
    auto &registry = get_registry();

    auto view = registry.view<const position, velocity>();

    view.each([](const auto &pos, auto &vel) {
        fmt::print("pos: {}, vel: {}\n", std::string{pos.vec}, std::string{vel.vec});
        vel.vec.x += 1.0;
        vel.vec.y += 2.0;
    });
}

int main() {
    auto &registry = get_registry();

    for (auto index = 0u; index < 10u; ++index) {
        const auto entity = registry.create();
        registry.emplace<position>(entity, vec3_t{index * 1., index * 1.});
        if (index % 2 == 0 || index % 3 == 0) {
            registry.emplace<velocity>(entity, vec3_t{index * .1, index * .1});
        }
    }

    register_schedule_callback(schedule_phase_t::update, update);

    run_schedule();
    run_schedule();
}
