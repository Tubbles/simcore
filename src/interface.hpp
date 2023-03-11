#pragma once

// clang-format off

#define INTERFACE(name)                                                  /* Cannot use parens here, NOLINT(bugprone-macro-parentheses) */ \
    constexpr name() noexcept = default;                                 /* Cannot use parens here, NOLINT(bugprone-macro-parentheses) */ \
    constexpr name(const name &) noexcept = default;                     /* Cannot use parens here, NOLINT(bugprone-macro-parentheses) */ \
    constexpr name(name &&) noexcept = default;                          /* Cannot use parens here, NOLINT(bugprone-macro-parentheses) */ \
    constexpr auto operator=(const name &) noexcept -> name & = default; /* Cannot use parens here, NOLINT(bugprone-macro-parentheses) */ \
    constexpr auto operator=(name &&) noexcept -> name & = default;      /* Cannot use parens here, NOLINT(bugprone-macro-parentheses) */ \
    virtual ~name() noexcept = default                                   /* Cannot use parens here, NOLINT(bugprone-macro-parentheses) */

// clang-format on
