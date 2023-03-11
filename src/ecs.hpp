#pragma once

#include "types.hpp"
#include "vec3.hpp"

#include <entt/entt.hpp>

extern entt::registry g_registry;

struct position {
    vec3_t vec;
};

struct velocity {
    vec3_t vec;
};

[[nodiscard]] constexpr auto get_registry() noexcept -> entt::registry & { return g_registry; }
