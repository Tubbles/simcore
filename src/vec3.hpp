#pragma once

#include "util.hpp"

#include <cassert>
#include <cmath>
#include <fmt/format.h>
#include <string>

// Members initialized through union
// NOLINTNEXTLINE(hicpp-member-init)
struct vec3_t {
    union {
        // Array is appropriate, std::array is not
        // NOLINTNEXTLINE(modernize-avoid-c-arrays)
        f64 e[3] = {0.0, 0.0, 0.0};
        struct {
            f64 x;
            f64 y;
            f64 z;
        };
    };

    // Members initialized through union
    // NOLINTNEXTLINE(hicpp-member-init)
    [[nodiscard]] constexpr vec3_t(f64 e0, f64 e1, f64 e2) noexcept : e{e0, e1, e2} {}
    // NOLINTNEXTLINE(hicpp-member-init)
    [[nodiscard]] constexpr vec3_t(f64 e0, f64 e1) noexcept : e{e0, e1, 0.0} {} // x,y ctor
    constexpr ~vec3_t() = default;

    // Blanket rule of 5
    // Members initialized through union
    // NOLINTNEXTLINE(hicpp-member-init)
    [[nodiscard]] constexpr vec3_t() noexcept = default;
    [[nodiscard]] constexpr vec3_t(const vec3_t &) noexcept = default;
    [[nodiscard]] constexpr vec3_t(vec3_t &&) noexcept = default;
    constexpr auto operator=(const vec3_t &) noexcept -> vec3_t & = default;
    constexpr auto operator=(vec3_t &&) noexcept -> vec3_t & = default;

    [[nodiscard]] constexpr auto operator-() const noexcept -> vec3_t { return vec3_t{-e[0], -e[1], -e[2]}; }

    [[nodiscard]] constexpr auto operator[](size_t i) const noexcept -> f64 {
        assert(i < ARR_LEN(e));
        return e[i]; // Array subscript checked, NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
    }

    // cppcheck-suppress functionConst; false positive
    [[nodiscard]] constexpr auto operator[](size_t i) noexcept -> f64 & {
        assert(i < ARR_LEN(e));
        return e[i]; // Array subscript checked, NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
    }

    constexpr auto operator+=(const vec3_t &v) noexcept -> vec3_t & {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    constexpr auto operator*=(const f64 t) noexcept -> vec3_t & {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    constexpr auto operator/=(const f64 t) noexcept -> vec3_t & { return *this *= 1 / t; }

    [[nodiscard]] constexpr auto operator+(const vec3_t &other) const noexcept -> vec3_t {
        return vec3_t{this->e[0] + other.e[0], this->e[1] + other.e[1], this->e[2] + other.e[2]};
    }

    [[nodiscard]] constexpr auto operator-(const vec3_t &other) const noexcept -> vec3_t {
        return vec3_t{this->e[0] - other.e[0], this->e[1] - other.e[1], this->e[2] - other.e[2]};
    }

    [[nodiscard]] constexpr auto operator*(const vec3_t &other) const noexcept -> f64 {
        return this->e[0] * other.e[0] + this->e[1] * other.e[1] + this->e[2] * other.e[2];
    }

    [[nodiscard]] constexpr auto elem_mult(const vec3_t &other) const noexcept -> vec3_t {
        return vec3_t{this->e[0] * other.e[0], this->e[1] * other.e[1], this->e[2] * other.e[2]};
    }

    [[nodiscard]] constexpr auto operator*(f64 t) const noexcept -> vec3_t {
        return vec3_t{t * this->e[0], t * this->e[1], t * this->e[2]};
    }

    [[nodiscard]] constexpr auto operator/(f64 t) const noexcept -> vec3_t { return *this * (1 / t); }

    [[nodiscard]] constexpr auto length_squared() const noexcept -> f64 {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    [[nodiscard]] constexpr auto length() const noexcept -> f64 { return std::sqrt(length_squared()); }

    [[nodiscard]] constexpr auto unit() const noexcept -> vec3_t { return *this / this->length(); }

    [[nodiscard]] constexpr auto dot(const vec3_t &other) const noexcept -> f64 { return this->operator*(other); }

    [[nodiscard]] constexpr auto cross(const vec3_t &other) const noexcept -> vec3_t {
        return vec3_t{this->e[1] * other.e[2] - this->e[2] * other.e[1],
                      this->e[2] * other.e[0] - this->e[0] * other.e[2],
                      this->e[0] * other.e[1] - this->e[1] * other.e[0]};
    }

    [[nodiscard]] explicit operator std::string() const noexcept {
        return fmt::format("({}, {}, {})", e[0], e[1], e[2]);
    }

    [[nodiscard]] auto to_string() const noexcept -> std::string { return std::string{*this}; }
};

[[nodiscard]] inline constexpr auto operator*(f64 t, const vec3_t &v) -> vec3_t { return v * t; }

namespace std {
[[nodiscard]] inline constexpr auto pow(const vec3_t &v, f64 p) noexcept -> f64 {
    return ::std::pow(::std::sqrt(v.dot(v)), p);
};

[[nodiscard]] inline constexpr auto sqrt(const vec3_t &v) noexcept -> f64 { return ::std::pow(v, 0.5); };
} // namespace std

[[nodiscard]] inline auto lerp(const vec3_t &start, const vec3_t &end, f64 t) noexcept -> vec3_t {
    return (1.0 - t) * start + t * end;
}

using point_t = vec3_t;
using color_t = vec3_t;
